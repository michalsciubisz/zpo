#ifndef INCLUDE_CORE_MODELS_IBONUSALLOWABLE_HPP_
#define INCLUDE_CORE_MODELS_IBONUSALLOWABLE_HPP_

namespace SystemCore {
    class IBonusAllowable {
    public:
        virtual void add_bonus_allowance() = 0;
    };
}

#endif /* INCLUDE_CORE_MODELS_IBONUSALLOWABLE_HPP_ */
