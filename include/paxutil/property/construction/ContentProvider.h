//
// Created by Bittner on 10/01/2019.
//

#ifndef PAXENGINE3_CONTENTPROVIDER_H
#define PAXENGINE3_CONTENTPROVIDER_H

#include <string>
#include <sstream>
#include <memory>
#include <optional>
#include <any>

#include "paxutil/macros/Definitions.h"
#include "paxutil/reflection/TypeHandle.h"

namespace PAX {
    class ContentProvider {
    protected:
        virtual std::any provideType(const TypeHandle & type) = 0;
        virtual std::any provideEncapsulated(const TypeHandle & elementType, const TypeHandle & containerType) = 0;

    public:
        ContentProvider();
        virtual ~ContentProvider();

        template<typename T, typename TContainer>
        std::optional<TContainer> getAs() {
            std::any val;

            if PAX_CONSTEXPR_IF (std::is_same<T, TContainer>::value) {
                val = provideType(paxtypeid(T));
            } else {
                val = provideEncapsulated(paxtypeid(T), paxtypeid(TContainer));
            }

            if (val.has_value()) {
                try {
                    return std::optional<TContainer>(std::any_cast<TContainer>(val));
                } catch (const std::bad_any_cast &badAnyCast) {}
            }

            return std::optional<TContainer>();
        }

        template<typename T, typename TContainer>
        TContainer requireAs() noexcept(false) {
            std::optional<TContainer> opt = getAs<T, TContainer>();

            if (opt.has_value())
                return opt.value();

            std::stringstream errormsg;
            errormsg << "[PAX::ContentProvider::requireAs<" << paxtypeid(T).name() << ", " << paxtypeid(TContainer).name() << ">] Required type could not be obtained!" << std::endl;
            std::cerr << errormsg.str();
            throw std::logic_error(errormsg.str());
        }

        template<typename T>
        std::optional<T> get() {
            return getAs<T, T>();
        }

        template<typename T>
        T require() noexcept(false) {
            return requireAs<T, T>();
        }

        template<typename T>
        std::optional<std::shared_ptr<T>> getSharedPtr() {
            return getAs<T, std::shared_ptr<T>>();
        }

        template<typename T>
        std::shared_ptr<T> requireSharedPtr() {
            return requireAs<T, std::shared_ptr<T>>();
        }
    };
}

#endif //PAXENGINE3_CONTENTPROVIDER_H
