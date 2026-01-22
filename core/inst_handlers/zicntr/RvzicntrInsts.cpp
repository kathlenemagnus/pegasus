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
    void RvzicntrInsts::getCsrPostUpdateActions(
        InstHandlers::CsrUpdateActionsMap & csrPostUpdate_actions)
    {
        static_assert(std::is_same_v<XLEN, RV64> || std::is_same_v<XLEN, RV32>);

        // Cycle
        csrPostUpdate_actions.emplace(
            CYCLE,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, CYCLE>,
                                          RvzicntrInsts>(nullptr, "cyclePostUpdate"));
        csrPostUpdate_actions.emplace(
            CYCLEH,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, CYCLE>,
                                          RvzicntrInsts>(nullptr, "cyclePostUpdate"));
        csrPostUpdate_actions.emplace(
            MCYCLE,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, MCYCLE>,
                                          RvzicntrInsts>(nullptr, "cyclePostUpdate"));
        csrPostUpdate_actions.emplace(
            MCYCLEH,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, MCYCLE>,
                                          RvzicntrInsts>(nullptr, "cyclePostUpdate"));
        csrPostUpdate_actions.emplace(
            TIME, pegasus::Action::createAction<&RvzicntrInsts::timePostUpdateHandler_<XLEN>,
                                                RvzicntrInsts>(nullptr, "timePostUpdate"));
        csrPostUpdate_actions.emplace(
            TIMEH, pegasus::Action::createAction<&RvzicntrInsts::timePostUpdateHandler_<XLEN>,
                                                 RvzicntrInsts>(nullptr, "timePostUpdate"));
        csrPostUpdate_actions.emplace(
            INSTRET,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, INSTRET>,
                                          RvzicntrInsts>(nullptr, "instretPostUpdate"));
        csrPostUpdate_actions.emplace(
            INSTRETH,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, INSTRET>,
                                          RvzicntrInsts>(nullptr, "instretPostUpdate"));
        csrPostUpdate_actions.emplace(
            MINSTRET,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, MINSTRET>,
                                          RvzicntrInsts>(nullptr, "instretPostUpdate"));
        csrPostUpdate_actions.emplace(
            MINSTRETH,
            pegasus::Action::createAction<&RvzicntrInsts::counterPostUpdateHandler_<XLEN, MINSTRET>,
                                          RvzicntrInsts>(nullptr, "instretPreUpdate"));
    }

    template void RvzicntrInsts::getCsrPostUpdateActions<RV32>(InstHandlers::CsrUpdateActionsMap &);
    template void RvzicntrInsts::getCsrPostUpdateActions<RV64>(InstHandlers::CsrUpdateActionsMap &);

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

    template <typename XLEN, uint32_t CSR>
    Action::ItrType RvzicntrInsts::counterPostUpdateHandler_(pegasus::PegasusState* state,
                                                             Action::ItrType action_it)
    {
        if constexpr (std::is_same_v<XLEN, RV64>)
        {
            const XLEN csr_val = READ_CSR_REG<XLEN>(state, CSR);
            state->getCachedCsrs()->at(CSR) = csr_val - 1;
        }
        else
        {
            const uint32_t RV32_CSR = (CSR == CYCLE) ? CYCLEH : MCYCLEH;
            const uint64_t csr_val = READ_CSR_REG<XLEN>(state, CSR);
            const uint64_t csrh_val = READ_CSR_REG<XLEN>(state, RV32_CSR);
            state->getCachedCsrs()->at(CSR) = ((csrh_val << 32) | csr_val) - 1;
        }
        return ++action_it;
    }

    template <typename XLEN>
    Action::ItrType RvzicntrInsts::timePostUpdateHandler_(pegasus::PegasusState* state,
                                                          Action::ItrType action_it)
    {
        if constexpr (std::is_same_v<XLEN, RV64>)
        {
            const XLEN csr_val = READ_CSR_REG<XLEN>(state, TIME);
            state->getCachedCsrs()->at(TIME) = csr_val - 1;
        }
        else
        {
            const uint64_t csr_val = READ_CSR_REG<XLEN>(state, TIME);
            const uint64_t csrh_val = READ_CSR_REG<XLEN>(state, TIMEH);
            state->getCachedCsrs()->at(TIME) = ((csrh_val << 32) | csr_val) - 1;
        }
        return ++action_it;
    }
} // namespace pegasus
