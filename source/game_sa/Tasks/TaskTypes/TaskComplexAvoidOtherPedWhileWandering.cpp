#include "StdInc.h"

#include "TaskComplexAvoidOtherPedWhileWandering.h"

void CTaskComplexAvoidOtherPedWhileWandering::InjectHooks() {
    RH_ScopedClass(CTaskComplexAvoidOtherPedWhileWandering);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x66A100);
}

// 0x66A100
CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(CPed* ped, const CVector& targetPoint, int32 moveState) : CTaskComplex() {
    m_ped       = ped;
    field_1C    = targetPoint;
    field_28    = targetPoint;
    m_moveState = static_cast<eMoveState>(moveState); // todo: change signature
    m_flag1     = false;
    m_flag2     = false;
    m_flag3     = false;
    m_flag4     = false;

    CEntity::SafeRegisterRef(m_ped);
}

// 0x66A1D0
CTaskComplexAvoidOtherPedWhileWandering::~CTaskComplexAvoidOtherPedWhileWandering() {
    CEntity::SafeCleanUpRef(m_ped);
}

CTaskComplexAvoidOtherPedWhileWandering* CTaskComplexAvoidOtherPedWhileWandering::Constructor(CPed* ped, const CVector& targetPoint, int32 moveState) {
    this->CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(ped, targetPoint, moveState);
    return this;
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::Clone() const {
    return plugin::CallMethodAndReturn<CTask*, 0x66D050, const CTaskComplexAvoidOtherPedWhileWandering*>(this);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6721B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x66A260, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66A2C0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x674610, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::QuitIK(CPed* ped) {
    return plugin::CallMethod<0x66A230, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

uint8 CTaskComplexAvoidOtherPedWhileWandering::NearbyPedsInSphere(CColSphere* colSphere, CPed* ped) {
    return plugin::CallMethodAndReturn<uint8, 0x66A320, CTaskComplexAvoidOtherPedWhileWandering*, CColSphere*, CPed*>(this, colSphere, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::SetUpIK(CPed* ped) {
    return plugin::CallMethod<0x66A850, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeSphere(CPed* ped, CColSphere* colSphere, CPed** pedsToCheck, CPed** pedsInSphere) {
    return plugin::CallMethodAndReturn<bool, 0x671FE0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*, CPed**, CPed**>(this, ped, colSphere, pedsToCheck, pedsInSphere);
}

void CTaskComplexAvoidOtherPedWhileWandering::ComputeAvoidSphere(CPed* ped, CColSphere* colSphere) {
    return plugin::CallMethod<0x672080, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colSphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeDetourTarget(CPed* ped, CColSphere* colSphere) {
    return plugin::CallMethodAndReturn<bool, 0x66A7B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colSphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeDetourTarget(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x672180, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}
