#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
template <typename T>
class ItemsWeightChecker
{
public:
	ItemsWeightChecker(int maximumWeight) : isActivated(false), maximumWeight(maximumWeight)
	{
	}

	void increaseMaximumWeight(int value)
	{
		this->maximumWeight += value;
	}

	void decreaseMaximumWeight(int value)
	{
		this->maximumWeight = (std::max)( this->maximumWeight - value, 0 );
	}

	std::string getMessageAboutWeight(std::shared_ptr<std::vector<std::shared_ptr<T>>> items)
	{
		std::string currentWeightMessage = "Current weight is: " + std::to_string(calculateItemsWeight(items));
		std::string activationMessage;
		if (isActivated) 
		{
			activationMessage = "\nMaximum weight: " + std::to_string(maximumWeight);
		}
		else
		{
			activationMessage = "\nWeight limitation is disabled";
		}
		return currentWeightMessage + activationMessage;
	}

	void changeActivation() {
		isActivated = !isActivated;
	}

	bool allowsToCarryNewItem(std::shared_ptr<std::vector<std::shared_ptr<T>>> items, std::shared_ptr<T> item)
	{
		if (isActivated)
		{
			int itemsWeight = calculateItemsWeight(items);
			if (itemsWeight > maximumWeight)
			{
				throw std::logic_error("Increase maximum weight or drop some items.");
			}
			return itemsWeight + item->getWeight() <= maximumWeight;
		}
		return true;
	}
private:
	int calculateItemsWeight(std::shared_ptr<std::vector<std::shared_ptr<T>>> items)
	{
		int itemsWeight = 0;
		for (auto item : *items)
		{
			itemsWeight += item->getWeight();
		}
		return itemsWeight;
	}

	int maximumWeight;
	bool isActivated;
};

