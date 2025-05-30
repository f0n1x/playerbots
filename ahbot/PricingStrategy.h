#pragma once
#include "Config/Config.h"
#include "Entities/ItemPrototype.h"

namespace ahbot
{
    class Category;

    class PricingStrategy
    {
    public:
        PricingStrategy(Category* category) : category(category) {}
        virtual ~PricingStrategy() {}

    public:
        virtual uint32 GetSellPrice(ItemPrototype const* proto, uint32 auctionHouse, bool ignoreMarket = false, std::ostringstream *explain = NULL);
        virtual uint32 GetBuyPrice(ItemPrototype const* proto, uint32 auctionHouse, std::ostringstream *explain = NULL);
        double GetMarketPrice(uint32 itemId, uint32 auctionHouse);
        virtual double GetRarityPriceMultiplier(uint32 itemId);
        virtual double GetLevelPriceMultiplier(ItemPrototype const* proto);
        static uint32 RoundPrice(double price);

    protected:
        virtual uint32 GetDefaultBuyPrice(ItemPrototype const* proto);
        virtual uint32 GetDefaultSellPrice(ItemPrototype const* proto);
        virtual double GetQualityMultiplier(ItemPrototype const* proto);
        virtual double GetCategoryPriceMultiplier(uint32 untilTime, uint32 auctionHouse);
        virtual double GetItemPriceMultiplier(ItemPrototype const* proto, uint32 untilTime, uint32 auctionHouse);
        double GetMultiplier(double count, double firstBuyTime, double lastBuyTime);
        double CalculatePrice(std::ostringstream *explain, ...);

    protected:
        Category* category;
    };

    class BuyOnlyRarePricingStrategy : public PricingStrategy
    {
    public:
        BuyOnlyRarePricingStrategy(Category* category) : PricingStrategy(category) {}

    public:
        virtual uint32 GetBuyPrice(ItemPrototype const* proto, uint32 auctionHouse, std::ostringstream *explain = NULL);
        virtual uint32 GetSellPrice(ItemPrototype const* proto, uint32 auctionHouse, bool ignoreMarket = false, std::ostringstream *explain = NULL);
    };

    class PricingStrategyFactory
    {
    public:
        static PricingStrategy* Create(std::string name, Category* category)
        {
            if (name == "buyOnlyRare")
                return new BuyOnlyRarePricingStrategy(category);

            return new PricingStrategy(category);
        }
    };
};
