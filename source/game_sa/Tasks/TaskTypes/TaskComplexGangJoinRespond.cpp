#include "StdInc.h"

#include "TaskComplexGangJoinRespond.h"
// #include "TaskComplexTurnToFaceEntityOrCoord.h"

void CTaskComplexGangJoinRespond::InjectHooks() {
    RH_ScopedClass(CTaskComplexGangJoinRespond);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6616F0);
    RH_ScopedInstall(Destructor, 0x661720);

    RH_ScopedVirtualInstall2(Clone, 0x662290, { .reversed = false });
    RH_ScopedVirtualInstall2(MakeAbortable, 0x661790, { .reversed = false });
    RH_ScopedVirtualInstall2(CreateNextSubTask, 0x6617A0, { .reversed = false });
    RH_ScopedVirtualInstall2(CreateFirstSubTask, 0x6618D0, { .reversed = false });
    RH_ScopedVirtualInstall2(ControlSubTask, 0x661950, { .reversed = false });
}

// 0x6616F0
CTaskComplexGangJoinRespond::CTaskComplexGangJoinRespond(uint8 a2) : CTaskComplex() {
    m_response = a2;
    m_animsReferenced = false;
}

// 0x661720
CTaskComplexGangJoinRespond::~CTaskComplexGangJoinRespond() {
    if (m_animsReferenced) {
        CAnimManager::RemoveAnimBlockRef(CAnimManager::GetAnimationBlockIndex("gangs"));
        m_animsReferenced = false;
    }
}

// 0x6617A0
CTask* CTaskComplexGangJoinRespond::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6617A0, CTaskComplexGangJoinRespond*, CPed*>(this, ped);
}

// 0x6618D0
CTask* CTaskComplexGangJoinRespond::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6618D0, CTaskComplexGangJoinRespond*, CPed*>(this, ped);
    // b10 = 0;
    // return new CTaskComplexTurnToFaceEntityOrCoord(FindPlayerPed(0), 0.5f, 0.2f);
}

// 0x661950
CTask* CTaskComplexGangJoinRespond::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x661950, CTaskComplexGangJoinRespond*, CPed*>(this, ped);
}
