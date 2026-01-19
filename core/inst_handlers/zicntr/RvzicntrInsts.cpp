#include "core/inst_handlers/zicntr/RvzicntrInsts.hpp"
#include "include/ActionTags.hpp"
#include "core/ActionGroup.hpp"
#include "core/PegasusCore.hpp"
#include "core/PegasusInst.hpp"
#include "core/Exception.hpp"
#include "core/Trap.hpp"

#include "include/gen/CSRBitMasks32.hpp"

namespace pegasus
{
    template <typename XLEN>
    void
    RvzicntrInsts::getCsrPreUpdateActions(InstHandlers::CsrUpdateActionsMap & csrPreUpdate_actions)
    {
        static_assert(std::is_same_v<XLEN, RV64> || std::is_same_v<XLEN, RV32>);

        // Cycle
        csrPreUpdate_actions.emplace(
            CYCLE, pegasus::Action::createAction<&RvzicntrInsts::cyclePreUpdateHandler_<XLEN>,
                                                 RvzicntrInsts>(nullptr, "cyclePreUpdate"));
        csrPreUpdate_actions.emplace(
            CYCLEH, pegasus::Action::createAction<&RvzicntrInsts::cyclePreUpdateHandler_<XLEN>,
                                                  RvzicntrInsts>(nullptr, "cyclePreUpdate"));
        csrPreUpdate_actions.emplace(
            MCYCLE, pegasus::Action::createAction<&RvzicntrInsts::cyclePreUpdateHandler_<XLEN>,
                                                  RvzicntrInsts>(nullptr, "cyclePreUpdate"));
        csrPreUpdate_actions.emplace(
            MCYCLEH, pegasus::Action::createAction<&RvzicntrInsts::cyclePreUpdateHandler_<XLEN>,
                                                   RvzicntrInsts>(nullptr, "cyclePreUpdate"));
        csrPreUpdate_actions.emplace(
            TIME, pegasus::Action::createAction<&RvzicntrInsts::timePreUpdateHandler_<XLEN>,
                                                RvzicntrInsts>(nullptr, "timePreUpdate"));
        csrPreUpdate_actions.emplace(
            TIMEH, pegasus::Action::createAction<&RvzicntrInsts::timePreUpdateHandler_<XLEN>,
                                                 RvzicntrInsts>(nullptr, "timePreUpdate"));
        csrPreUpdate_actions.emplace(
            INSTRET, pegasus::Action::createAction<&RvzicntrInsts::instretPreUpdateHandler_<XLEN>,
                                                   RvzicntrInsts>(nullptr, "instretPreUpdate"));
        csrPreUpdate_actions.emplace(
            INSTRETH, pegasus::Action::createAction<&RvzicntrInsts::instretPreUpdateHandler_<XLEN>,
                                                    RvzicntrInsts>(nullptr, "instretPreUpdate"));
        csrPreUpdate_actions.emplace(
            MINSTRET, pegasus::Action::createAction<&RvzicntrInsts::instretPreUpdateHandler_<XLEN>,
                                                    RvzicntrInsts>(nullptr, "instretPreUpdate"));
        csrPreUpdate_actions.emplace(
            MINSTRETH, pegasus::Action::createAction<&RvzicntrInsts::instretPreUpdateHandler_<XLEN>,
                                                     RvzicntrInsts>(nullptr, "instretPreUpdate"));
    }

    template void RvzicntrInsts::getCsrPreUpdateActions<RV32>(InstHandlers::CsrUpdateActionsMap &);
    template void RvzicntrInsts::getCsrPreUpdateActions<RV64>(InstHandlers::CsrUpdateActionsMap &);

    template <typename XLEN>
    Action::ItrType RvzicntrInsts::cyclePreUpdateHandler_(pegasus::PegasusState* state,
                                                          Action::ItrType action_it)
    {
        state->updateCycleCsrs<XLEN>();
        return ++action_it;
    }

    template <typename XLEN>
    Action::ItrType RvzicntrInsts::timePreUpdateHandler_(pegasus::PegasusState* state,
                                                         Action::ItrType action_it)
    {
        state->updateTimeCsrs<XLEN>();
        return ++action_it;
    }

    template <typename XLEN>
    Action::ItrType RvzicntrInsts::instretPreUpdateHandler_(pegasus::PegasusState* state,
                                                            Action::ItrType action_it)
    {
        state->updateInstretCsrs<XLEN>();
        return ++action_it;
    }
} // namespace pegasus
