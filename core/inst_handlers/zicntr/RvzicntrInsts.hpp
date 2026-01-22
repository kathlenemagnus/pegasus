#pragma once

#include "core/InstHandlers.hpp"
#include "core/inst_handlers/zicsr/RvcsrAccess.hpp"

namespace pegasus
{
    class PegasusState;

    class RvzicntrInsts : public RvCsrAccess
    {
      public:
        using base_type = RvzicntrInsts;

        template <typename XLEN>
        static void getCsrPreUpdateActions(InstHandlers::CsrUpdateActionsMap &);

        template <typename XLEN>
        static void getCsrPostUpdateActions(InstHandlers::CsrUpdateActionsMap &);

      private:
        // CSR pre-update Actions
        // cycle(h), mcycle(h)
        template <typename XLEN>
        Action::ItrType cyclePreUpdateHandler_(pegasus::PegasusState* state,
                                               Action::ItrType action_it);
        // time(h)
        template <typename XLEN>
        Action::ItrType timePreUpdateHandler_(pegasus::PegasusState* state,
                                              Action::ItrType action_it);
        // instret(h), minstret(h)
        template <typename XLEN>
        Action::ItrType instretPreUpdateHandler_(pegasus::PegasusState* state,
                                                 Action::ItrType action_it);

        // CSR post-update Actions
        // cycle(h), mcycle(h), instret(h), minstret(h)
        template <typename XLEN, uint32_t CSR>
        Action::ItrType counterPostUpdateHandler_(pegasus::PegasusState* state,
                                                  Action::ItrType action_it);
        // time(h)
        template <typename XLEN>
        Action::ItrType timePostUpdateHandler_(pegasus::PegasusState* state,
                                               Action::ItrType action_it);
    };
} // namespace pegasus
