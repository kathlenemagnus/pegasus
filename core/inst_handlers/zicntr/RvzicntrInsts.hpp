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

      private:
        // CSR pre-update Actions
        template <typename XLEN>
        Action::ItrType cyclePreUpdateHandler_(pegasus::PegasusState* state,
                                               Action::ItrType action_it);
        template <typename XLEN>
        Action::ItrType timePreUpdateHandler_(pegasus::PegasusState* state,
                                              Action::ItrType action_it);
        template <typename XLEN>
        Action::ItrType instretPreUpdateHandler_(pegasus::PegasusState* state,
                                                 Action::ItrType action_it);
    };
} // namespace pegasus
