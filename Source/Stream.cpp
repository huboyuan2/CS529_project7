//------------------------------------------------------------------------------
//
// File Name:	Level2Scene.h
// Author(s):	Boyuan Hu
// Course:		CS529F25
// Project:		Project 2
// Purpose:		Template class for a new scene.
//
// Copyright ?2025 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "Precompiled.h"
#include "Stream.h"
#include <string_view>
#include <vector>
#include <nlohmann/json.hpp>
#include <dragon/assert.h>
#include <dragon/platform_dependencies.h>
#include "LoggingSystem.h"
#include "Vector2D.h"
namespace CS529
{
    Stream::Stream(std::string_view filePath)
    {
		Open(filePath);
    }

    Stream::~Stream(void)
    {

    }
    // @brief Reads the contents of an array by iterating through the array items.
// @brief Specific Steps:
// @brief   If the stream contains 'key' (the 1st parameter),
// @brief     Traverse down the tree to the 'key' node (PushNode).
// @brief     Iterate through the array items (use 'dataNode->items()').
// @brief       Push the current dataNode onto the dataStack.
// @brief       Set the dataNode equal to the current value (e.g. item.value()).
// @brief       Invoke the lambda function, passing current key (the component Name).
// @brief       Return to the previous location in the tree (PopNode).
// @brief     Return to the previous location in the tree (PopNode).
//
// @param key = The key associated with the array (AKA value) to be read.
// @param lambda = A function to be called for each item in the array.
    void Stream::ReadArray(std::string_view key, std::function<void()> lambda)
    {
        if (!Contains(key))
            return;
        PushNode(key);
        for (const auto& [index, value] : dataNode->items())
        {
            dataStack.push_back(dataNode);
            dataNode = &value;
            lambda();
            PopNode();
        }
        PopNode();
    }
    // @brief Reads the contents of an object by iterating through the key:value pairs.
        // @brief Specific Steps:
        // @brief   If the stream contains 'key' (the 1st parameter),
        // @brief     Traverse down the tree to the 'key' node (PushNode).
        // @brief     Iterate through the component key-value pairs (use 'dataNode->items()').
        // @brief       Invoke the lambda function, passing current key (the component Name).
        // @brief     Return to the previous location in the tree (PopNode).
        //
        // @param key = The key associated with the object (AKA value) to be read.
        // @param lambda = A function to be called for each key:value in the object.
    void Stream::ReadObject(std::string_view key, std::function<void(const std::string& key)> lambda)
    {
        if (!Contains(key))
            return;
		PushNode(key);
		for (const auto& [componentName, componentValue] : dataNode->items())
		{
			lambda(componentName);
		}
		PopNode();
    }

    bool Stream::Open(std::string_view filePath)
    {
        std::ifstream file(filePath.data());
        if (!file.is_open()) {
			LoggingSystem::Error("Stream: Failed to open file: {}", filePath);
			return isValid; 
        }
        try
        {
            file >> jsonData;
			dataNode = new json(jsonData);
        }
        catch (const json::parse_error& exception)
        {
            LoggingSystem::Error("Stream: JSON parse error in file {}:", filePath, exception.what());
			return isValid;
		}
        isValid = true;
        return isValid;
    }
    bool Stream::Contains(std::string_view key)
    {
		return dataNode&& (dataNode->contains(key));
    }
    // @brief Get the requested object, pushing the previous node onto the data stack.
    // @brief Specific Steps:
    // @brief   if (Contains(key))
    // @brief     Push the 'data' pointer onto the back of the data stack.
    // @brief     Set the 'data' pointer to the address of the value "at(key)".
    void Stream::PushNode(std::string_view key)
    {
        if(!Contains(key))
			return; 
        dataStack.push_back(dataNode);
        dataNode = new json(dataNode->at(key));
		
       
        //dataStack.pop_back();
    }
    // @brief Pops the last stored json node, traversing back up the tree.
    // @brief Specific Steps:
    // @brief   Set the 'data' pointer to the last element of the data stack.
    // @brief   Pop the last node from the data stack.
    void Stream::PopNode()
    {
        if (dataStack.empty())
            return;
        dataNode = dataStack.back();
		dataStack.pop_back();
        
    }
}