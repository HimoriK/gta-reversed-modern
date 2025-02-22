#pragma once

#include "Base.h"
#include "Vector.h"

#include "TaskSimple.h"

class CPed;

class CTaskSimpleWaitUntilPedIsOutCar : public CTaskSimple {
public:
    CPed*   m_PedToWaitFor;
    bool    m_bIsNotGoingTowardsPos;
    CVector m_Pos;

public:
    static constexpr auto Type = TASK_SIMPLE_WAIT_UNTIL_PED_OUT_CAR;

    CTaskSimpleWaitUntilPedIsOutCar(CPed * ped, CVector const& pos);
    ~CTaskSimpleWaitUntilPedIsOutCar() override;

    CTask* Clone() const override { return new CTaskSimpleWaitUntilPedIsOutCar(m_PedToWaitFor, m_Pos); }
    eTaskType GetTaskType() const override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override { return true; }
    bool ProcessPed(CPed * ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleWaitUntilPedIsOutCar* Constructor(CPed * ped, CVector const& pos) { this->CTaskSimpleWaitUntilPedIsOutCar::CTaskSimpleWaitUntilPedIsOutCar(ped, pos); return this; }
    CTaskSimpleWaitUntilPedIsOutCar* Destructor() { this->CTaskSimpleWaitUntilPedIsOutCar::~CTaskSimpleWaitUntilPedIsOutCar(); return this; }

    CTask * Clone_Reversed() { return CTaskSimpleWaitUntilPedIsOutCar::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleWaitUntilPedIsOutCar::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed * ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleWaitUntilPedIsOutCar::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed * ped) { return CTaskSimpleWaitUntilPedIsOutCar::ProcessPed(ped); }
};
VALIDATE_SIZE(CTaskSimpleWaitUntilPedIsOutCar, 0x1C);
