#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <concepts>
#include <cstdint>
#include <mutex>

namespace dragon::events
{
    /// @brief A token for identifying a registered event handler.
    /// 
    /// @details Contains the event's memory address as a unique ID and the handler's index.
    /// Members are read-only and accessible via getter methods.
    class EventToken
    {
    public:
        EventToken() noexcept = default;
        EventToken(EventToken const&) = default;
        explicit EventToken(std::nullptr_t) noexcept {};
        
        EventToken& operator=(EventToken const&) noexcept = default;
        EventToken& operator=(std::nullptr_t) noexcept {
            return operator=(EventToken{nullptr});
        }

        /// @brief Constructs a token with the specified event ID and handler index.
        /// 
        /// @param event_id The unique ID of the event instance (memory address).
        /// @param index The index of the handler in the event's handler vector.
        EventToken(std::size_t event_id, std::size_t index) noexcept
            : event_id_(event_id), index_(index) {
        }

        /// @brief Gets the event ID.
        /// 
        /// @return The unique ID of the event instance.
        std::size_t event_id() const noexcept { return event_id_; }

        /// @brief Gets the handler index.
        /// 
        /// @return The index of the handler in the event's handler vector.
        std::size_t index() const noexcept { return index_; }

    private:
        std::size_t event_id_{ 0 }; ///< Unique ID of the event instance (memory address).
        std::size_t index_{ 0 };    ///< Index of the handler in the vector.
    };

    /// @brief A type-safe event handler that wraps a callable with a specific signature.
    /// 
    /// @tparam Args Parameter types for the event handler.
    /// @details Encapsulates a callable (function pointer, lambda, or member function with object)
    /// that can be invoked with the specified argument types. Provides safe invocation and lifetime
    /// management for bound objects.
    template<typename... Args>
    class EventHandler
    {
    public:
        /// @brief Default constructor creating an empty handler.
        /// 
        /// @details The handler is initialized with no callable and will not invoke anything when called.
        EventHandler() noexcept = default;

        /// @brief Constructs an event handler from a function pointer.
        /// 
        /// @param func A function pointer with signature void(Args...).
        EventHandler(void (*func)(Args...)) noexcept
            : handler_(func) {
        }

        /// @brief Constructs an event handler from a compatible callable (e.g., lambda or functor).
        /// 
        /// @param callable A callable object compatible with void(Args...).
        /// @details The callable is stored in a function wrapper.
        template<typename Callable>
            requires std::invocable<Callable, Args...> 
        EventHandler(Callable&& callable) noexcept
            : handler_{ std::forward<Callable>(callable) } {
        }

        /// @brief Constructs an event handler from a shared_ptr and a member function pointer.
        /// 
        /// @param obj A shared_ptr to the object owning the member function.
        /// @param mem_fn A member function pointer with signature void(T::*)(Args...).
        /// @details Creates a lambda that invokes the member function on the object.
        template<typename T>
        EventHandler(std::shared_ptr<T> obj, void (T::* mem_fn)(Args...)) noexcept
            : handler_([obj, mem_fn](Args... args) {
            (*obj.*mem_fn)(std::forward<Args>(args)...);
                }) {
        }

        /// @brief Constructs an event handler from a weak_ptr and a member function pointer.
        /// 
        /// @param weak_obj A weak_ptr to the object owning the member function.
        /// @param mem_fn A member function pointer with signature void(T::*)(Args...).
        /// @details Creates a lambda that checks the weak_ptr before invoking the member function.
        template<typename T>
        EventHandler(std::weak_ptr<T> weak_obj, void (T::* mem_fn)(Args...)) noexcept
            : handler_([weak_obj, mem_fn](Args... args) {
            if (auto obj = weak_obj.lock()) {
                (*obj.*mem_fn)(std::forward<Args>(args)...);
            }
                }) {
        }

        /// @brief Invokes the stored callable with the provided arguments.
        /// 
        /// @param args Arguments to pass to the callable.
        /// @details Does nothing if the handler is empty (default-constructed).
        void invoke(Args... args) const {
            if (handler_) {
                handler_(std::forward<Args>(args)...);
            }
        }

        /// @brief Checks if the handler is empty (default-constructed).
        /// 
        /// @return true if the handler is empty, false otherwise.
        explicit operator bool() const noexcept {
            return static_cast<bool>(handler_);
        }

    private:
        std::function<void(Args...)> handler_; ///< The stored callable.
        // note: theoretically we might be tempted to use std::move_only_function for efficiency.  
        // But this precludes the Event class from taking a snapshot copy of its EventHandler vector during 
        // event invocation (which is a very desireable feature, as we do not want to hold the lock while invoking all the hanlders).
    };

    /// @brief Manages a collection of event handlers for a specific event.
    /// 
    /// @tparam Args Parameter types for the event handlers.
    /// 
    /// @details Stores event handlers and provides methods to add, remove, and invoke them.
    /// The class is thread-safe for adding, removing, and invoking handlers.
    template<typename... Args>
    class Event
    {
    public:
        using Handler = EventHandler<Args...>; ///< Type alias for the event handler.

        /// @brief Default constructor.
        /// 
        /// @details Ensures the event's pointer size is compatible with std::size_t.
        Event() noexcept {
        }

        /// @brief Adds a handler to the event.
        /// 
        /// @param handler The event handler to add. 
        /// 
        /// @return A token that can be used to remove the handler.
        EventToken add(Handler&& handler) {
            std::scoped_lock lock(mutex_);
            handlers_.push_back(std::move(handler));
            return { id(), handlers_.size() - 1 };
        }

        /// \overload
        template<typename T>
        EventToken add(std::shared_ptr<T> obj, void (T::* mem_fn)(Args...)) noexcept
        {
            return add(EventHandler<Args...>(std::move(obj), mem_fn));
        }

        /// \overload
        template<typename T>
        EventToken add(std::weak_ptr<T> weak_obj, void (T::* mem_fn)(Args...)) noexcept
        {
            return add(EventHandler<Args...>(std::move(weak_obj), mem_fn));
        }

        /// @brief Removes a handler using its token.
        /// 
        /// @param token The token of the handler to remove.
        void remove(EventToken token) {
            std::scoped_lock lock(mutex_);
            if (token.event_id() == id() && token.index() < handlers_.size()) {
                handlers_[token.index()] = Handler{};
            }
        }

        /// @brief Invokes all registered handlers with the provided arguments.
        /// 
        /// @param args Arguments to pass to each handler.
        /// 
        /// @details Exceptions thrown by handlers are not caught, allowing them to propagate.
        void invoke(Args... args) const {
            std::vector<Handler> local_handlers;
            {
                std::scoped_lock lock(mutex_);
                local_handlers = handlers_;
            }
            for (auto& handler : local_handlers) {
                if (handler) {
                    handler.invoke(std::forward<Args>(args)...);
                }
            }
        }

        /// @brief Attempts to invoke all registered handlers with the provided arguments.
        /// 
        /// @param args Arguments to pass to each handler.
        /// 
        /// @details Catches exceptions thrown by handlers to prevent one handler's failure from affecting others.
        /// Also catches exceptions that might occur during the locking or copying of the handlers vector.
        void tryInvoke(Args... args) const noexcept {
            try {
                std::vector<Handler> local_handlers;
                {
                    std::scoped_lock lock(mutex_);
                    local_handlers = handlers_;
                }
                for (auto& handler : local_handlers) {
                    if (handler) {
                        try {
                            handler.invoke(std::forward<Args>(args)...);
                        }
                        catch (...) {
                            // Handle the exception gracefully, e.g., log it or ignore it.
                            // This prevents one handler's failure from affecting others.
                            // In your application, you might want to log the error or take other actions.
                        }
                    }
                }
            }
            catch (...) {
                // Handle any exceptions that might occur from locking or copying the handlers vector.
                // This is a catch-all to ensure that the event system remains robust.
                // In your application, you might want to log the error or take other actions.
            }
        }

    private:
        // a unique ID for this event instance.
        std::size_t id() const noexcept {
            static_assert(sizeof(Event*) == sizeof(std::size_t), "Event pointer size must match std::size_t for safe casting");
            return reinterpret_cast<std::size_t>(this);
        }

        std::vector<Handler> handlers_; ///< Collection of registered handlers.
        mutable std::mutex mutex_;      ///< Mutex for thread safety.
    };
}
