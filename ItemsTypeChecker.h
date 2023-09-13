#pragma once
#include <sstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <set>
template <typename T>
class ItemsTypeChecker
{
public:
	ItemsTypeChecker(std::initializer_list<std::string> allowedTypes)
	{
		this->allowedTypes = std::shared_ptr<std::set<std::string>>(new std::set<std::string>(allowedTypes));
	}

	void addAllowedType(const std::string& allowedType)
	{
		allowedTypes->insert(allowedType);
	}

	void removeAllowedType(const std::string& unallowedType)
	{
		allowedTypes->erase(unallowedType);
	}

	std::string getMessageAboutAllowedTypes()
	{
		std::stringstream allowedTypesMessage;
		allowedTypesMessage << "Allowed types:";
		for (auto allowedType : *allowedTypes)
		{
			allowedTypesMessage << " " << allowedType;
		}
		return allowedTypesMessage.str();
	}

	bool allowsToCarryNewItem(std::shared_ptr<std::vector<std::shared_ptr<T>>> items, std::shared_ptr<T> item)
	{
		if (!areCarryingItemsAllowed(items))
		{
			throw std::logic_error("Is actually carrying unallowed item. Drop them first or add as allowed.");
		}
		return isItemAllowed(item);
	}
private:
	bool isItemAllowed(std::shared_ptr<T> item)
	{
		auto itemName = item->getName();
		auto search = allowedTypes->find(itemName);
		if (search != allowedTypes->end())
		{
			return true;
		}
		return false;
	}

	bool areCarryingItemsAllowed(std::shared_ptr<std::vector<std::shared_ptr<T>>> items)
	{
		for (auto item : *items)
		{
			if (!isItemAllowed(item))
			{
				return false;
			}
		}
		return true;
	}

	std::shared_ptr<std::set<std::string>> allowedTypes;
};

