/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Physical.h"

float& CPhysical::DAMPING_LIMIT_IN_FRAME = *(float*)0x8CD7A0;
float& CPhysical::DAMPING_LIMIT_OF_SPRING_FORCE = *(float*)0x8CD7A4;
float& CPhysical::PHYSICAL_SHIFT_SPEED_DAMP = *(float*)0x8CD788;
float& CPhysical::SOFTCOL_SPEED_MULT = *(float*)0x8CD794;
float& CPhysical::SOFTCOL_SPEED_MULT2 = *(float*)0x8CD798;
float& CPhysical::SOFTCOL_DEPTH_MIN = *(float*)0x8CD78C;
float& CPhysical::SOFTCOL_DEPTH_MULT = *(float*)0x8CD790;
float& CPhysical::SOFTCOL_CARLINE_SPEED_MULT = *(float*)0x8CD79C;
float& CPhysical::TEST_ADD_AMBIENT_LIGHT_FRAC = *(float*)0x8CD7B8;
float& CPhysical::HIGHSPEED_ELASTICITY_MULT_COPCAR = *(float*)0x8CD784;
CVector& CPhysical::fxDirection = *(CVector*)0xB73720;

void CPhysical::InjectHooks()
{
    using namespace ReversibleHooks;
    Install("CPhysical", "RemoveAndAdd", 0x542560, &CPhysical::RemoveAndAdd);
    Install("CPhysical", "ApplyTurnForce", 0x542A50, &CPhysical::ApplyTurnForce);
    Install("CPhysical", "ApplyForce", 0x542B50, &CPhysical::ApplyForce);
    Install("CPhysical", "GetSpeed", 0x542CE0, &CPhysical::GetSpeed);
    // Install("CPhysical", "ApplyMoveSpeed", 0x542DD0, &CPhysical::ApplyMoveSpeed); // Go to the function definition and see why this is commented
    Install("CPhysical", "ApplyTurnSpeed", 0x542E20, &CPhysical::ApplyTurnSpeed);
    Install("CPhysical", "ApplyMoveForce_vec", 0x5429F0, (void(CPhysical::*)(CVector force)) & CPhysical::ApplyMoveForce);
    Install("CPhysical", "SetDamagedPieceRecord", 0x5428C0, &CPhysical::SetDamagedPieceRecord);
    Install("CPhysical", "RemoveFromMovingList", 0x542860, &CPhysical::RemoveFromMovingList);
    Install("CPhysical", "AddToMovingList", 0x542800, &CPhysical::AddToMovingList);
    Install("CPhysical", "Add_Reversed", 0x544A30, &CPhysical::Add_Reversed);
    Install("CPhysical", "Remove_Reversed", 0x5424C0, &CPhysical::Remove_Reversed); 
    Install("CPhysical", "GetBoundRect_Reversed", 0x5449B0, &CPhysical::GetBoundRect_Reversed);
    Install("CPhysical", "ProcessControl_Reversed", 0x5485E0, &CPhysical::ProcessControl_Reversed);
    Install("CPhysical", "ProcessCollision_Reversed", 0x54DFB0, &CPhysical::ProcessCollision_Reversed);
    Install("CPhysical", "ProcessShift_Reversed", 0x54DB10, &CPhysical::ProcessShift_Reversed);
    Install("CPhysical", "TestCollision_Reversed", 0x54DEC0, &CPhysical::TestCollision_Reversed);
    Install("CPhysical", "ProcessEntityCollision_Reversed", 0x546D00, &CPhysical::ProcessEntityCollision_Reversed);
    Install("CPhysical", "ApplyGravity", 0x542FE0, &CPhysical::ApplyGravity);
    Install("CPhysical", "ApplyFrictionMoveForce", 0x5430A0, &CPhysical::ApplyFrictionMoveForce);
    Install("CPhysical", "ApplyFrictionForce", 0x543220, &CPhysical::ApplyFrictionForce);
    Install("CPhysical", "SkipPhysics", 0x5433B0, &CPhysical::SkipPhysics);
    Install("CPhysical", "AddCollisionRecord", 0x543490, &CPhysical::AddCollisionRecord);
    Install("CPhysical", "GetHasCollidedWith", 0x543540, &CPhysical::GetHasCollidedWith);
    Install("CPhysical", "GetHasCollidedWithAnyObject", 0x543580, &CPhysical::GetHasCollidedWithAnyObject);
    Install("CPhysical", "ApplyCollision_1", 0x5435C0, (bool(CPhysical::*)(CEntity*, CColPoint&, float&)) & CPhysical::ApplyCollision);
    Install("CPhysical", "ApplySoftCollision_1", 0x543890, (bool(CPhysical::*)(CEntity*, CColPoint&, float&)) & CPhysical::ApplySoftCollision);
    Install("CPhysical", "ApplySpringCollision", 0x543C90, &CPhysical::ApplySpringCollision);
    Install("CPhysical", "ApplySpringCollisionAlt", 0x543D60, &CPhysical::ApplySpringCollisionAlt);
    Install("CPhysical", "ApplySpringDampening", 0x543E90, &CPhysical::ApplySpringDampening);
    Install("CPhysical", "RemoveRefsToEntity", 0x544280, &CPhysical::RemoveRefsToEntity);
    Install("CPhysical", "DettachEntityFromEntity", 0x5442F0, &CPhysical::DettachEntityFromEntity);
    Install("CPhysical", "DettachAutoAttachedEntity", 0x5446A0, &CPhysical::DettachAutoAttachedEntity);
    Install("CPhysical", "GetLightingFromCol", 0x5447B0, &CPhysical::GetLightingFromCol);
    Install("CPhysical", "GetLightingTotal", 0x544850, &CPhysical::GetLightingTotal);
    Install("CPhysical", "CanPhysicalBeDamaged", 0x5448B0, &CPhysical::CanPhysicalBeDamaged);
    Install("CPhysical", "ApplyAirResistance", 0x544C40, &CPhysical::ApplyAirResistance);
    Install("CPhysical", "ApplyCollisionAlt", 0x544D50, &CPhysical::ApplyCollisionAlt);
    Install("CPhysical", "ApplyFriction_self", 0x5454C0, (bool(CPhysical::*)(float, CColPoint&)) & CPhysical::ApplyFriction);
    Install("CPhysical", "ApplyFriction_other", 0x545980, (bool(CPhysical::*)(CPhysical*, float, CColPoint&)) &CPhysical::ApplyFriction);
    Install("CPhysical", "ProcessShiftSectorList", 0x546670, &CPhysical::ProcessShiftSectorList);
    Install("CPhysical", "ApplySpeed", 0x547B80, &CPhysical::ApplySpeed);
    Install("CPhysical", "UnsetIsInSafePosition", 0x548320, &CPhysical::UnsetIsInSafePosition);
    Install("CPhysical", "ApplyFriction_void", 0x5483D0, (void(CPhysical::*)()) & CPhysical::ApplyFriction);
    Install("CPhysical", "ApplyCollision_2", 0x548680, (bool(CPhysical::*)(CEntity*, CColPoint&, float&, float&)) & CPhysical::ApplyCollision);
    Install("CPhysical", "ApplySoftCollision_2", 0x54A2C0, (bool(CPhysical::*)(CPhysical*, CColPoint&, float&, float&))&CPhysical::ApplySoftCollision);
    Install("CPhysical", "ProcessCollisionSectorList", 0x54BA60, &CPhysical::ProcessCollisionSectorList);
    Install("CPhysical", "ProcessCollisionSectorList_SimpleCar", 0x54CFF0, &CPhysical::ProcessCollisionSectorList_SimpleCar);
    Install("CPhysical", "AttachEntityToEntity_vec", 0x54D570, (void(CPhysical::*)(CPhysical*, CVector, CVector))&CPhysical::AttachEntityToEntity);
    Install("CPhysical", "AttachEntityToEntity_quat", 0x54D690, (void(CPhysical::*)(CPhysical*, CVector*, CQuaternion*))&CPhysical::AttachEntityToEntity);
    Install("CPhysical", "CheckCollision", 0x54D920, &CPhysical::CheckCollision);
    Install("CPhysical", "CheckCollision_SimpleCar", 0x54DAB0, &CPhysical::CheckCollision_SimpleCar);
    Install("CPhysical", "PlacePhysicalRelativeToOtherPhysical", 0x546DB0, &CPhysical::PlacePhysicalRelativeToOtherPhysical);
    Install("CPhysical", "PositionAttachedEntity", 0x546FF0, &CPhysical::PositionAttachedEntity);
}

CPhysical::CPhysical() : CEntity()
{
    m_pCollisionList.m_pNode = nullptr;
    CPlaceable::AllocateStaticMatrix();
    GetMatrix().SetUnity();

    m_fMass = 1.0F;
    m_fTurnMass = 1.0F;
    m_fVelocityFrequency = 1.0F;
    m_fAirResistance = 0.1F;
    m_pMovingList = nullptr;
    m_nFakePhysics = false;
    m_nNumEntitiesCollided = 0;
    memset(m_apCollidedEntities, 0, sizeof(m_apCollidedEntities));
    m_nPieceType = 0;
    m_fDamageIntensity = 0.0F;
    m_pDamageEntity = nullptr;
    m_bUsesCollision = true;
    m_fMovingSpeed = 0.0F;
    m_pAttachedTo = nullptr;
    m_pEntityIgnoredCollision = nullptr;
    m_fDynamicLighting = 0.0F;
    m_pShadowData = nullptr;
    field_38 = 100.0F;
    m_fContactSurfaceBrightness = 1.0F;

    m_nPhysicalFlags = 0;
    physicalFlags.bApplyGravity = true;
}

CPhysical::~CPhysical()
{
    if (m_pShadowData)
        g_realTimeShadowMan.ReturnRealTimeShadow(m_pShadowData);

    m_pCollisionList.Flush();
}

void CPhysical::Add()
{
    CPhysical::Add_Reversed();
}

void CPhysical::Add_Reversed()
{
    if (m_bIsBIGBuilding) {
        CEntity::Add();
        return;
    }

    CRect boundRect;
    GetBoundRect(&boundRect);
    int32 startSectorX = CWorld::GetSectorX(boundRect.left);
    int32 startSectorY = CWorld::GetSectorY(boundRect.top);
    int32 endSectorX = CWorld::GetSectorX(boundRect.right);
    int32 endSectorY = CWorld::GetSectorY(boundRect.bottom);
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CPtrListDoubleLink* doubleLinkList = nullptr;
            CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
            switch (m_nType) {
            case ENTITY_TYPE_VEHICLE:
                doubleLinkList = &repeatSector->m_lists[REPEATSECTOR_VEHICLES];
                break;
            case ENTITY_TYPE_PED:
                doubleLinkList = &repeatSector->m_lists[REPEATSECTOR_PEDS];
                break;
            case ENTITY_TYPE_OBJECT:
                doubleLinkList = &repeatSector->m_lists[REPEATSECTOR_OBJECTS];
                break;
            }

            auto newEntityInfoNode = new CEntryInfoNode();
            if (newEntityInfoNode) {
                auto newDoubleLink = doubleLinkList->AddItem(this);
                newEntityInfoNode->m_pDoubleLink = newDoubleLink;
                newEntityInfoNode->m_pRepeatSector = repeatSector;
                newEntityInfoNode->m_pDoubleLinkList = doubleLinkList;
            }
            newEntityInfoNode->AddToList(m_pCollisionList.m_pNode);
            m_pCollisionList.m_pNode = newEntityInfoNode;
        }
    }
}

// 0x5424C0
void CPhysical::Remove()
{
    CPhysical::Remove_Reversed();
}

void CPhysical::Remove_Reversed()
{
    if (m_bIsBIGBuilding) {
        CEntity::Remove();
    } else {
        CEntryInfoNode* entryInfoNode = m_pCollisionList.m_pNode;
        while (entryInfoNode) {
            CEntryInfoNode* nextEntryInfoNode = entryInfoNode->m_pNext;
            entryInfoNode->m_pDoubleLinkList->DeleteNode(entryInfoNode->m_pDoubleLink);
            m_pCollisionList.DeleteNode(entryInfoNode);

            entryInfoNode = nextEntryInfoNode;
        }
    }
}

// 0x5449B0
CRect* CPhysical::GetBoundRect(CRect* rect)
{
    return CPhysical::GetBoundRect_Reversed(rect);
}

CRect* CPhysical::GetBoundRect_Reversed(CRect* rect)
{
    CVector boundCentre;
    CEntity::GetBoundCentre(&boundCentre);
    float fRadius = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundRadius();
    *rect = CRect(boundCentre.x - fRadius, boundCentre.y - fRadius, boundCentre.x + fRadius, boundCentre.y + fRadius);
    return rect;
}

// 0x5485E0
void CPhysical::ProcessControl()
{
    CPhysical::ProcessControl_Reversed();
}

void CPhysical::ProcessControl_Reversed()
{
    if (m_nType != ENTITY_TYPE_PED)
        physicalFlags.bSubmergedInWater = false;

    m_bHasHitWall = false;
    m_bWasPostponed = false;
    m_bIsInSafePosition = false;
    m_bHasContacted = false;

    if (m_nStatus != STATUS_SIMPLE)
    {
        physicalFlags.b31 = false;
        physicalFlags.bOnSolidSurface = false;
        m_nNumEntitiesCollided = 0;
        m_nPieceType = 0;
        m_fDamageIntensity = 0.0f;
        if (m_pDamageEntity)
            m_pDamageEntity->CleanUpOldReference(&m_pDamageEntity);
        m_pDamageEntity = nullptr;
        ApplyFriction();
        if (!m_pAttachedTo || physicalFlags.bInfiniteMass)
        {
            ApplyGravity();
            ApplyAirResistance();
        }
    }
}

// 0x54DFB0
void CPhysical::ProcessCollision()
{
    ProcessCollision_Reversed();
}

void CPhysical::ProcessCollision_Reversed()
{
    m_fMovingSpeed = 0.0f;
    physicalFlags.bProcessingShift = false;
    physicalFlags.b13 = false;
    if (m_bUsesCollision && !physicalFlags.bDisableSimpleCollision)  {
        if (m_nStatus == STATUS_SIMPLE) {
            if (CheckCollision_SimpleCar() && m_nStatus == STATUS_SIMPLE) {
                m_nStatus = STATUS_PHYSICS;
                if (m_nType == ENTITY_TYPE_VEHICLE)
                    CCarCtrl::SwitchVehicleToRealPhysics(static_cast<CVehicle*>(this));
            }
            m_bIsStuck = false;
            m_bIsInSafePosition = true;
            RemoveAndAdd();
            return;
        }

        auto* vehicle = static_cast<CVehicle*>(this);
        auto* automobile = static_cast<CAutomobile*>(this);
        auto* bike = static_cast<CBike*>(this);
        if (m_nStatus == STATUS_TRAILER) {
            CColPoint* pWheelsColPoints = nullptr;
            float* pfWheelsSuspensionCompression = nullptr;
            CVector* pWheelsCollisionPositions = nullptr;
            if (vehicle->m_vehicleSubType) {
                bike->m_apWheelCollisionEntity[0] = nullptr; // todo: enum
                bike->m_apWheelCollisionEntity[1] = nullptr;
                bike->m_apWheelCollisionEntity[2] = nullptr;
                bike->m_apWheelCollisionEntity[3] = nullptr;
                pWheelsColPoints = bike->m_anWheelColPoint;
                pfWheelsSuspensionCompression = bike->m_fWheelsSuspensionCompression;
                pWheelsCollisionPositions = bike->m_avTouchPointsLocalSpace;
            }
            else {
                automobile->m_pWheelCollisionEntity[0] = nullptr;
                automobile->m_pWheelCollisionEntity[1] = nullptr;
                automobile->m_pWheelCollisionEntity[2] = nullptr;
                automobile->m_pWheelCollisionEntity[3] = nullptr;
                pWheelsColPoints = automobile->m_wheelColPoint;
                pfWheelsSuspensionCompression = automobile->m_fWheelsSuspensionCompression;
                pWheelsCollisionPositions = automobile->m_vWheelCollisionPos;
            }
            CCollisionData* colData = GetColModel()->m_pColData;
            int32 collisionIndex = 0;
            while (true) {
                int32 colLinesCount = colData->m_nNumLines;
                if (colData->bUsesDisks)
                    colLinesCount = 0;
                if (collisionIndex >= colLinesCount) {
                    m_bIsStuck = false;
                    m_bIsInSafePosition = true;
                    m_vecMoveSpeed.z = 0.0f;
                    m_vecTurnSpeed.x = 0.0f;
                    m_vecTurnSpeed.y = 0.0f;
                    m_matrix->ForceUpVector(CVector(0.0f, 0.0f, 1.0f));
                    GetPosition().z = CCarCtrl::FindGhostRoadHeight(vehicle) + vehicle->GetHeightAboveRoad();
                    ApplySpeed();
                    m_matrix->Reorthogonalise();
                    RemoveAndAdd();
                    vehicle->vehicleFlags.bVehicleColProcessed = true;
                    return;
                }

                CColPoint* pWheelColPoint = &pWheelsColPoints[collisionIndex];
                CColLine* pColLine = &colData->m_pLines[collisionIndex];
                CVector vecColLinePosStart = *m_matrix * pColLine->m_vecStart;
                CVector vecColLinePosEnd = *m_matrix * pColLine->m_vecEnd;
                pWheelColPoint->m_vecNormal = CVector(0.0f, 0.0f, 1.0f);
                pWheelColPoint->m_nSurfaceTypeA = SURFACE_WHEELBASE;
                pWheelColPoint->m_nSurfaceTypeB = SURFACE_TARMAC;
                pWheelColPoint->m_fDepth = 0.0f;
                float fGhostRoadHeight = CCarCtrl::FindGhostRoadHeight(vehicle);
                if (fGhostRoadHeight <= vecColLinePosStart.z) {
                    if (fGhostRoadHeight > vecColLinePosEnd.z) {
                        float fWheelSuspensionCompression = (vecColLinePosStart.z - fGhostRoadHeight) / (vecColLinePosStart.z - vecColLinePosEnd.z);
                        pfWheelsSuspensionCompression[collisionIndex] = fWheelSuspensionCompression;
                        pWheelColPoint->m_vecPoint = (vecColLinePosEnd - vecColLinePosStart) * fWheelSuspensionCompression + vecColLinePosStart;
                    }
                    else {
                        pfWheelsSuspensionCompression[collisionIndex] = 1.0f;
                        pWheelColPoint->m_vecPoint = vecColLinePosEnd;
                    }
                }
                else {
                    pfWheelsSuspensionCompression[collisionIndex] = 0.0f;
                    pWheelColPoint->m_vecPoint = vecColLinePosStart;
                }
                pWheelsCollisionPositions[collisionIndex] = pWheelColPoint->m_vecPoint - GetPosition();
                collisionIndex++;
            }
        }
        CVector vecOldMoveSpeed = m_vecMoveSpeed;
        float fOldTimeStep = CTimer::GetTimeStep();
        float fOldElasticity = m_fElasticity;
        CMatrix oldEntityMatrix(*m_matrix);
        bool bProcessCollisionBeforeSettingTimeStep = false;
        bool bUnknown = false;
        uint8 collisionSteps = SpecialEntityCalcCollisionSteps(&bProcessCollisionBeforeSettingTimeStep, &bUnknown);
        float fStep = fOldTimeStep / collisionSteps;
        if (bProcessCollisionBeforeSettingTimeStep)
        {
            ApplySpeed();
            m_matrix->Reorthogonalise();
            physicalFlags.bProcessingShift = false;
            physicalFlags.b13 = false;
            physicalFlags.b17 = true;
            bool bOldUsesCollision = m_bUsesCollision;
            m_bUsesCollision = false;
            if (!CheckCollision())
            {
                physicalFlags.b17 = false;
                m_bUsesCollision = bOldUsesCollision;
                if (m_nType == ENTITY_TYPE_VEHICLE)
                    vehicle->vehicleFlags.bVehicleColProcessed = true;
                m_bIsStuck = false;
                m_bIsInSafePosition = true;
                physicalFlags.bProcessCollisionEvenIfStationary = false;
                physicalFlags.b13 = false;
                m_fElasticity = fOldElasticity;
                m_fMovingSpeed = DistanceBetweenPoints(oldEntityMatrix.GetPosition(), GetPosition());
                RemoveAndAdd();
                return;
            }
            m_bUsesCollision = bOldUsesCollision;
            physicalFlags.b17 = false;
            *static_cast<CMatrix*>(m_matrix) = oldEntityMatrix;
            m_vecMoveSpeed = vecOldMoveSpeed;
            if (m_nType == ENTITY_TYPE_VEHICLE && vehicle->vehicleFlags.bIsLawEnforcer)
                m_fElasticity *= HIGHSPEED_ELASTICITY_MULT_COPCAR;
        }

        CPed* ped = static_cast<CPed*>(this);
        if (collisionSteps > 1u)
        {
            for (uint8 stepIndex = 1; stepIndex < collisionSteps; stepIndex++)
            {
                CTimer::UpdateTimeStep(stepIndex * fStep);
                ApplySpeed();
                bool bCheckCollision = CheckCollision();
                if (m_nType == ENTITY_TYPE_PED && m_vecMoveSpeed.z == 0.0f && !ped->bWasStanding && ped->bIsStanding) {
                    oldEntityMatrix.GetPosition().z = GetPosition().z;
                }
                *static_cast<CMatrix*>(m_matrix) = oldEntityMatrix;
                CTimer::UpdateTimeStep(fOldTimeStep);
                if (bCheckCollision) {
                    m_fElasticity = fOldElasticity;
                    return;
                }
                if (m_nType == ENTITY_TYPE_VEHICLE) {
                    if (vehicle->m_vehicleType) {
                        if (vehicle->m_vehicleType == VEHICLE_BIKE) {
                            bike->m_fWheelsSuspensionCompression[0] = 1.0f; // todo: enum
                            bike->m_fWheelsSuspensionCompression[1] = 1.0f;
                            bike->m_fWheelsSuspensionCompression[2] = 1.0f;
                            bike->m_fWheelsSuspensionCompression[3] = 1.0f;
                        }
                        else if (vehicle->m_vehicleType == VEHICLE_TRAILER) {
                            automobile->m_fWheelsSuspensionCompression[0] = 1.0f;
                            automobile->m_fWheelsSuspensionCompression[1] = 1.0f;
                            automobile->m_fWheelsSuspensionCompression[2] = 1.0f;
                        }
                    }
                    else {
                        automobile->m_fWheelsSuspensionCompression[0] = 1.0f;
                        automobile->m_fWheelsSuspensionCompression[1] = 1.0f;
                        automobile->m_fWheelsSuspensionCompression[2] = 1.0f;
                        automobile->m_fWheelsSuspensionCompression[3] = 1.0f;
                    }
                }
            }
        }

        ApplySpeed();
        m_matrix->Reorthogonalise();
        physicalFlags.bProcessingShift = false;
        physicalFlags.b13 = false;
        if (   m_vecMoveSpeed != 0.0f
            || m_vecTurnSpeed != 0.0f
            || physicalFlags.bProcessCollisionEvenIfStationary
            || m_nStatus == STATUS_PLAYER
            || m_nType == ENTITY_TYPE_VEHICLE && vehicle->vehicleFlags.bIsCarParkVehicle
            || m_nType == ENTITY_TYPE_PED && (ped->IsPlayer() || ped->bTestForBlockedPositions|| !ped->bIsStanding)) 
        {
            if (m_nType == ENTITY_TYPE_VEHICLE)
                vehicle->vehicleFlags.bVehicleColProcessed = true;
            if (CheckCollision()) {
                *static_cast<CMatrix*>(m_matrix) = oldEntityMatrix;
                m_fElasticity = fOldElasticity;
                return;
            }
        }
        else if (m_nType == ENTITY_TYPE_PED) {
            ped->bIsStanding = true;
        }
        m_bIsStuck = false;
        m_bIsInSafePosition = true;
        physicalFlags.bProcessCollisionEvenIfStationary = false;
        physicalFlags.b13 = false;
        m_fElasticity = fOldElasticity;
        m_fMovingSpeed = DistanceBetweenPoints(oldEntityMatrix.GetPosition(), GetPosition());
        RemoveAndAdd();
        return;
    }
    m_bIsStuck = false;
    m_bIsInSafePosition = true;
    RemoveAndAdd();
}

// 0x54DB10
void CPhysical::ProcessShift()
{
    CPhysical::ProcessShift_Reversed();
}

// 0x54DEC0
bool CPhysical::TestCollision(bool bApplySpeed) {
   return CPhysical::TestCollision_Reversed(bApplySpeed);
}

bool CPhysical::TestCollision_Reversed(bool bApplySpeed) {
    CMatrix entityMatrix(*m_matrix);
    physicalFlags.b17 = true;
    physicalFlags.b13 = true;
    bool bOldUsesCollision = m_bUsesCollision;
    m_bUsesCollision = false;
    bool bTestForBlockedPositions = false;
    CPed* ped = static_cast<CPed*>(this);
    if (m_nType == ENTITY_TYPE_PED && ped->bTestForBlockedPositions) {
        bTestForBlockedPositions = true;
        ped->bTestForBlockedPositions = false;
    }
    if (bApplySpeed)
        ApplySpeed();
    bool bCheckCollision = CheckCollision();
    m_bUsesCollision = bOldUsesCollision;
    physicalFlags.b17 = false;
    physicalFlags.b13 = false;
    *(CMatrix*)m_matrix = entityMatrix;
    if (bTestForBlockedPositions)
        ped->bTestForBlockedPositions = true;
    return bCheckCollision;
}

// 0x546D00
int32 CPhysical::ProcessEntityCollision(CPhysical* entity, CColPoint* colpoint) {
    return CPhysical::ProcessEntityCollision_Reversed(entity, colpoint);
}

int32 CPhysical::ProcessEntityCollision_Reversed(CPhysical* entity, CColPoint* colpoint) {
    CColModel* colModel = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel();
    int32 totalColPointsToProcess = CCollision::ProcessColModels(*m_matrix, *colModel, entity->GetMatrix(), *entity->GetColModel(), colpoint, nullptr, nullptr, false);
    if (totalColPointsToProcess > 0) {
        AddCollisionRecord(entity);
        if (!entity->IsBuilding())
            entity->AddCollisionRecord(this);
        if (entity->IsBuilding() || entity->IsStatic())
            m_bHasHitWall = true;
    }
    return totalColPointsToProcess;
}

void CPhysical::ProcessShift_Reversed()
{
    CRect boundingBox;
    GetBoundRect(&boundingBox);
    m_fMovingSpeed = 0.0f;

    bool bPhysicalFlagsSet = m_nPhysicalFlags & (PHYSICAL_DISABLE_MOVE_FORCE | PHYSICAL_INFINITE_MASS | PHYSICAL_DISABLE_Z);
    if (m_nStatus == STATUS_SIMPLE || bPhysicalFlagsSet)
    {
        if (bPhysicalFlagsSet)
        {
            ResetTurnSpeed();
        }
        m_bIsStuck = false;
        m_bIsInSafePosition = true;
        RemoveAndAdd();
    }
    else
    {
        if (m_bHasHitWall)
        {
            CPed* ped = static_cast<CPed*>(this);
            bool bSomeSpecificFlagsSet = false;
            if (m_nType == ENTITY_TYPE_PED && ped->m_standingOnEntity)
            {
                if (!ped->m_standingOnEntity->m_bIsStatic || ped->m_standingOnEntity->m_bHasContacted)
                {
                    bSomeSpecificFlagsSet = true;
                }
            }
            if ((m_nType == ENTITY_TYPE_PED && bSomeSpecificFlagsSet) || CWorld::bSecondShift)
            {
                float fMoveSpeedShift = pow(CPhysical::PHYSICAL_SHIFT_SPEED_DAMP, CTimer::GetTimeStep());
                m_vecMoveSpeed *= fMoveSpeedShift;
                float fTurnSpeedShift = pow(CPhysical::PHYSICAL_SHIFT_SPEED_DAMP, CTimer::GetTimeStep());
                m_vecTurnSpeed *= fTurnSpeedShift;
            }
        }

        CMatrix oldEntityMatrix(*m_matrix);
        ApplySpeed();
        m_matrix->Reorthogonalise();
        SetNextScanCode();

        bool bShifted = false;
        if (m_nType == ENTITY_TYPE_VEHICLE)
        {
            physicalFlags.bProcessingShift = true;
        }

        int32 startSectorX = CWorld::GetSectorX(boundingBox.left);
        int32 startSectorY = CWorld::GetSectorY(boundingBox.top);
        int32 endSectorX = CWorld::GetSectorX(boundingBox.right);
        int32 endSectorY = CWorld::GetSectorY(boundingBox.bottom);
        for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
            for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
                if (ProcessShiftSectorList(sectorX, sectorY))
                    bShifted = true;
            }
        }
        physicalFlags.bProcessingShift = false;

        if (bShifted || m_nType == ENTITY_TYPE_VEHICLE) {
            CWorld::IncrementCurrentScanCode();
            bool bShifted2 = false;
            int32 startSectorX = CWorld::GetSectorX(boundingBox.left);
            int32 startSectorY = CWorld::GetSectorY(boundingBox.top);
            int32 endSectorX = CWorld::GetSectorX(boundingBox.right);
            int32 endSectorY = CWorld::GetSectorY(boundingBox.bottom);
            for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
                for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
                    if (ProcessCollisionSectorList(sectorX, sectorY)) {
                        if (!CWorld::bSecondShift) {
                            *(CMatrix*)m_matrix = oldEntityMatrix;
                            return;
                        }
                        bShifted2 = true;
                    }
                }
            } 
            if (bShifted2)
            {
                *(CMatrix*)m_matrix = oldEntityMatrix;
                return;
            }
        }
        m_bIsStuck = false;
        m_bIsInSafePosition = true;
        m_fMovingSpeed = (GetPosition() - oldEntityMatrix.GetPosition()).Magnitude();
        RemoveAndAdd();
    }
}

// 0x542560
void CPhysical::RemoveAndAdd()
{
    if (m_bIsBIGBuilding) {
        CEntity::Remove();
        CEntity::Add();
        return;
    }

    CEntryInfoNode* entryInfoNode = m_pCollisionList.m_pNode;
    CRect boundRect;
    GetBoundRect(&boundRect);
    int32 startSectorX = CWorld::GetSectorX(boundRect.left);
    int32 startSectorY = CWorld::GetSectorY(boundRect.top);
    int32 endSectorX = CWorld::GetSectorX(boundRect.right);
    int32 endSectorY = CWorld::GetSectorY(boundRect.bottom);
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CPtrListDoubleLink* doubleLinkList = nullptr;
            CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
            switch (m_nType) {
            case ENTITY_TYPE_VEHICLE:
                doubleLinkList = &repeatSector->m_lists[REPEATSECTOR_VEHICLES];
                break;
            case ENTITY_TYPE_PED:
                doubleLinkList = &repeatSector->m_lists[REPEATSECTOR_PEDS];
                break;
            case ENTITY_TYPE_OBJECT:
                doubleLinkList = &repeatSector->m_lists[REPEATSECTOR_OBJECTS];
                break;
            }

            if (entryInfoNode) {
                CPtrNodeDoubleLink* pDoubleLink = entryInfoNode->m_pDoubleLink;
                if (entryInfoNode->m_pDoubleLinkList->pNode == (CPtrNode*)pDoubleLink)
                    entryInfoNode->m_pDoubleLinkList->pNode = (CPtrNode*)pDoubleLink->pNext;

                CPtrNodeDoubleLink* pDoubleLinkPrevious = pDoubleLink->pPrev;
                if (pDoubleLinkPrevious)
                    pDoubleLinkPrevious->pNext = pDoubleLink->pNext;

                CPtrNodeDoubleLink* doubleLinkNext = pDoubleLink->pNext;
                if (doubleLinkNext)
                    doubleLinkNext->pPrev = pDoubleLink->pPrev;

                pDoubleLink->AddToList(doubleLinkList);

                entryInfoNode->m_pRepeatSector = repeatSector;
                entryInfoNode->m_pDoubleLinkList = doubleLinkList;
                entryInfoNode = entryInfoNode->m_pNext;
            } else {
                auto newDoubleLink = doubleLinkList->AddItem(this);
                auto newEntityInfoNode = new CEntryInfoNode();
                if (newEntityInfoNode) {
                    newEntityInfoNode->m_pDoubleLink = newDoubleLink;
                    newEntityInfoNode->m_pRepeatSector = repeatSector;
                    newEntityInfoNode->m_pDoubleLinkList = doubleLinkList;
                }
                newEntityInfoNode->AddToList(m_pCollisionList.m_pNode);
                m_pCollisionList.m_pNode = newEntityInfoNode;
            }
        }
    }

    while (entryInfoNode) {
        CEntryInfoNode* nextEntryInfoNode = entryInfoNode->m_pNext;
        entryInfoNode->m_pDoubleLinkList->DeleteNode(entryInfoNode->m_pDoubleLink);
        m_pCollisionList.DeleteNode(entryInfoNode);

        entryInfoNode = nextEntryInfoNode;
    }
}

// 0x542800
void CPhysical::AddToMovingList()
{
    if (!m_pMovingList && !m_bIsStaticWaitingForCollision)
    {
        auto pLink = CWorld::ms_listMovingEntityPtrs.AddItem(this);
        m_pMovingList = pLink;
    }
}

// 0x542860
void CPhysical::RemoveFromMovingList()
{
   auto pMovingList = m_pMovingList;
    if (pMovingList)
    {
        CWorld::ms_listMovingEntityPtrs.DeleteNode(m_pMovingList);
        m_pMovingList = nullptr;
    }
}

// 0x5428C0
void CPhysical::SetDamagedPieceRecord(float fDamageIntensity, CEntity* entity, CColPoint& colPoint, float fDistanceMult)
{
    auto* object = static_cast<CObject*>(this);
    if (fDamageIntensity > m_fDamageIntensity) {
        m_fDamageIntensity = fDamageIntensity;
        m_nPieceType = colPoint.m_nPieceTypeA;
        if (m_pDamageEntity)
            m_pDamageEntity->CleanUpOldReference(&m_pDamageEntity);
        m_pDamageEntity = entity;
        entity->RegisterReference(&m_pDamageEntity);
        m_vecLastCollisionPosn = colPoint.m_vecPoint;
        m_vecLastCollisionImpactVelocity = fDistanceMult * colPoint.m_vecNormal;
        if (IsObject() && colPoint.m_nSurfaceTypeB == SURFACE_CAR_MOVINGCOMPONENT)
            object->objectFlags.bDamaged = 1;
        else if (entity->IsObject() && colPoint.m_nSurfaceTypeA == SURFACE_CAR_MOVINGCOMPONENT)
            static_cast<CObject*>(entity)->objectFlags.bDamaged = 1;
    }

    if (physicalFlags.bDisableZ) {
        if (entity->m_nModelIndex == ModelIndices::MI_POOL_CUE_BALL && IsObject()) {
            object->m_nLastWeaponDamage = object->m_nLastWeaponDamage != 0xFF ? WEAPON_RUNOVERBYCAR : WEAPON_DROWNING;
        }
    }
}

// 0x4ABBA0
void CPhysical::ApplyMoveForce(float x, float y, float z)
{
    return ApplyMoveForce(CVector(x, y ,z));
}

// 0x5429F0
void CPhysical::ApplyMoveForce(CVector force)
{
    if (!physicalFlags.bInfiniteMass && !physicalFlags.bDisableMoveForce) {
        if (physicalFlags.bDisableZ)
            force.z = 0.0f;
        m_vecMoveSpeed += force / m_fMass;
    }
}

// 0x542A50
void CPhysical::ApplyTurnForce(CVector force, CVector point)
{
    if (!physicalFlags.bDisableTurnForce)
    {
        CVector vecCentreOfMassMultiplied;
        if (!physicalFlags.bInfiniteMass)
            vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);

        if (physicalFlags.bDisableMoveForce) {
            point.z = 0.0f;
            force.z = 0.0f;
        }
        CVector vecDifference = point - vecCentreOfMassMultiplied;
        m_vecTurnSpeed += CrossProduct(vecDifference, force) / m_fTurnMass;
    }
}

// 0x542B50
void CPhysical::ApplyForce(CVector vecForce, CVector point, bool bUpdateTurnSpeed)
{
    CVector vecMoveSpeedForce = vecForce;
    if (physicalFlags.bDisableZ)
        vecMoveSpeedForce.z = 0.0f;

    if (!physicalFlags.bInfiniteMass && !physicalFlags.bDisableMoveForce) 
        m_vecMoveSpeed += vecMoveSpeedForce / m_fMass;

    if (!physicalFlags.bDisableTurnForce && bUpdateTurnSpeed) {
        CVector vecCentreOfMassMultiplied;
        float fTurnMass = m_fTurnMass;
        if (physicalFlags.bInfiniteMass)
            fTurnMass += m_vecCentreOfMass.z * m_fMass * m_vecCentreOfMass.z * 0.5f;
        else
            vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);

        if (physicalFlags.bDisableMoveForce) {
            point.z = 0.0f;
            vecForce.z = 0.0f;
        }

        CVector distance = point - vecCentreOfMassMultiplied;
        m_vecTurnSpeed += CrossProduct(distance, vecForce) / fTurnMass;
    }
}

// 0x542CE0
CVector CPhysical::GetSpeed(CVector point)
{
    CVector vecCentreOfMassMultiplied;
    if (!physicalFlags.bInfiniteMass)
        vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);

    CVector distance = point - vecCentreOfMassMultiplied;
    CVector vecTurnSpeed = m_vecTurnSpeed + m_vecFrictionTurnSpeed;
    CVector speed = CrossProduct(vecTurnSpeed, distance);
    speed += m_vecMoveSpeed + m_vecFrictionMoveSpeed;
    return speed;
}

/*
    The code for this function is fine, but it will crash if we hook it. This function should be
    only hooked after reversing all references to this function: 
    CPhysical::ApplySpeed (done)
    CWorld::Process
    CAutoMobile::ProcessControlCollisionCheck
    CBike::ProcessControlCollisionCheck
    CTrain::ProcessControl (Done)
*/
void CPhysical::ApplyMoveSpeed()
{
    if (physicalFlags.bDontApplySpeed || physicalFlags.bDisableMoveForce)
        ResetMoveSpeed();
    else
        GetPosition() += CTimer::GetTimeStep() * m_vecMoveSpeed;
}

// 0x542E20
void CPhysical::ApplyTurnSpeed()
{
    if (physicalFlags.bDontApplySpeed) {
        ResetTurnSpeed();
    }
    else
    {
        CVector vecTurnSpeedTimeStep = CTimer::GetTimeStep() * m_vecTurnSpeed;
        CVector vecCrossProduct;
        CrossProduct(&vecCrossProduct, &vecTurnSpeedTimeStep, &GetRight());
        GetRight() += vecCrossProduct;
        CrossProduct(&vecCrossProduct, &vecTurnSpeedTimeStep, &GetForward());
        GetForward() += vecCrossProduct;
        CrossProduct(&vecCrossProduct, &vecTurnSpeedTimeStep, &GetUp());
        GetUp() += vecCrossProduct;
        if (!physicalFlags.bInfiniteMass && !physicalFlags.bDisableMoveForce) {
            CVector vecNegativeCentreOfMass = m_vecCentreOfMass * -1.0f;
            CVector vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), vecNegativeCentreOfMass);
            GetPosition() += CrossProduct(vecTurnSpeedTimeStep, vecCentreOfMassMultiplied);;
        }
    }
}

// 0x542FE0
void CPhysical::ApplyGravity()
{
    if (physicalFlags.bApplyGravity && !physicalFlags.bDisableMoveForce) {
        if (physicalFlags.bInfiniteMass) {
            float fMassTimeStep = CTimer::GetTimeStep() * m_fMass;
            CVector point = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
            CVector force (0.0f, 0.0f, fMassTimeStep * -0.008f);
            ApplyForce(force, point, true);
        }
        else if (m_bUsesCollision) {
            m_vecMoveSpeed.z -= CTimer::GetTimeStep() * 0.008f;
        }
    }
}

// 0x5430A0
void CPhysical::ApplyFrictionMoveForce(CVector moveForce)
{
    if (!physicalFlags.bInfiniteMass && !physicalFlags.bDisableMoveForce)
    {
        if (physicalFlags.bDisableZ)
        {
            moveForce.z = 0.0f;
        }
        m_vecFrictionMoveSpeed += moveForce / m_fMass;
    }
}

// Unused
// 0x543100
void CPhysical::ApplyFrictionTurnForce(CVector posn, CVector velocity)
{
    ((void(__thiscall*)(CPhysical*, CVector, CVector))0x543100)(this, posn, velocity);
}

// 0x543220
void CPhysical::ApplyFrictionForce(CVector vecMoveForce, CVector point)
{
    CVector vecTheMoveForce = vecMoveForce;

    if (physicalFlags.bDisableZ)
    {
        vecTheMoveForce.z = 0.0f;
    }

    if (!physicalFlags.bInfiniteMass && !physicalFlags.bDisableMoveForce)
    {
        m_vecFrictionMoveSpeed += vecTheMoveForce / m_fMass;
    }

    CVector vecCentreOfMassMultiplied;
    if (!physicalFlags.bDisableTurnForce)
    {
        float fTurnMass = m_fTurnMass;
        if (physicalFlags.bInfiniteMass)
            fTurnMass += m_vecCentreOfMass.z * m_fMass * m_vecCentreOfMass.z * 0.5f;
        else
            vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);

        if (physicalFlags.bDisableMoveForce)
        {
            point.z = 0.0f;
            vecMoveForce.z = 0.0f;
        }

        CVector vecDifference = point - vecCentreOfMassMultiplied;
        CVector vecMoveForceCrossProduct;
        vecMoveForceCrossProduct.Cross(vecDifference, vecMoveForce);

        m_vecFrictionTurnSpeed += vecMoveForceCrossProduct / fTurnMass;
    }
}

// 0x5433B0
void CPhysical::SkipPhysics()
{
    if (m_nType != ENTITY_TYPE_PED && m_nType != ENTITY_TYPE_VEHICLE)
        physicalFlags.bSubmergedInWater = false;

    m_bHasHitWall = false;
    m_bWasPostponed = false;
    m_bIsInSafePosition = false;
    m_bHasContacted = false;

    if (m_nStatus != STATUS_SIMPLE)
    {
        physicalFlags.bOnSolidSurface = false;
        m_nNumEntitiesCollided = 0;
        m_nPieceType = 0;
        m_fDamageIntensity = 0.0f;
        if (m_pDamageEntity)
            m_pDamageEntity->CleanUpOldReference(&m_pDamageEntity);
        m_pDamageEntity = nullptr;
        ResetFrictionTurnSpeed();
        ResetFrictionMoveSpeed();
    }
}

// 0x543490
void CPhysical::AddCollisionRecord(CEntity* collidedEntity)
{
    physicalFlags.bOnSolidSurface = true;
    m_nLastCollisionTime = CTimer::GetTimeInMS();
    if (m_nType == ENTITY_TYPE_VEHICLE)
    {
        auto* vehicle = static_cast<CVehicle*>(this);
        if (collidedEntity->m_nType == ENTITY_TYPE_VEHICLE)
        {
            auto* pCollidedVehicle = static_cast<CVehicle*>(collidedEntity);
            if (vehicle->m_nAlarmState == -1)
                vehicle->m_nAlarmState = 15000;
            if (pCollidedVehicle->m_nAlarmState == -1)
                pCollidedVehicle->m_nAlarmState = 15000;
        }
    }

    if (physicalFlags.bCanBeCollidedWith)
    {
        for (uint32 i = 0; i < m_nNumEntitiesCollided; i++)
        {
            if (m_apCollidedEntities[i] == collidedEntity)
                return;
        }

        if (m_nNumEntitiesCollided < 6) {
            m_apCollidedEntities[m_nNumEntitiesCollided] = collidedEntity;
            m_nNumEntitiesCollided++;
        }
    }
}

// 0x543540
bool CPhysical::GetHasCollidedWith(CEntity* entity)
{
    if (!physicalFlags.bCanBeCollidedWith || m_nNumEntitiesCollided <= 0)
        return false;

    for (uint32 i = 0; i < m_nNumEntitiesCollided; i++)
    {
        if (m_apCollidedEntities[i] == entity)
            return true;
    }
    return false;
}

// 0x543580
bool CPhysical::GetHasCollidedWithAnyObject()
{
    if (!physicalFlags.bCanBeCollidedWith || m_nNumEntitiesCollided <= 0)
        return false;

    for (uint32 i = 0; i < m_nNumEntitiesCollided; i++)
    {
        CEntity* pCollidedEntity = m_apCollidedEntities[i];
        if (pCollidedEntity && pCollidedEntity->m_nType == ENTITY_TYPE_OBJECT)
            return true;
    }
    return false;
}

// 0x5435C0
bool CPhysical::ApplyCollision(CEntity* entity, CColPoint& colPoint, float& damageIntensity)
{
    if (physicalFlags.bDisableTurnForce)
    {
        float fSpeedDotProduct = DotProduct(&m_vecMoveSpeed, &colPoint.m_vecNormal);
        if (fSpeedDotProduct < 0.0f)
        {
            damageIntensity = -(fSpeedDotProduct * m_fMass);
            CVector vecMoveSpeed = damageIntensity * colPoint.m_vecNormal;
            ApplyMoveForce(vecMoveSpeed.x, vecMoveSpeed.y, vecMoveSpeed.z);

            float fCollisionImpact1 = damageIntensity / m_fMass;
            AudioEngine.ReportCollision(this, entity, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
            return true;
        }
    }
    else
    {
        CVector vecDistanceToPoint = colPoint.m_vecPoint - GetPosition();
        CVector vecSpeed = GetSpeed(vecDistanceToPoint);

        CVector vecMoveDirection = colPoint.m_vecNormal;
        float fSpeedDotProduct = DotProduct(&vecMoveDirection, &vecSpeed);
        if (fSpeedDotProduct < 0.0f)
        {
            CVector vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
            CVector vecDifference = vecDistanceToPoint - vecCentreOfMassMultiplied;
            CVector vecSpeedCrossProduct;
            vecSpeedCrossProduct.Cross(vecDifference, vecMoveDirection);
            float fSquaredMagnitude = vecMoveDirection.SquaredMagnitude();
            float fCollisionMass = 1.0f / (fSquaredMagnitude / m_fTurnMass + 1.0f / m_fMass);

            damageIntensity = -((m_fElasticity + 1.0f) * fCollisionMass * fSpeedDotProduct);

            CVector vecMoveSpeed = vecMoveDirection * damageIntensity;
            if (m_nType == ENTITY_TYPE_VEHICLE && vecMoveDirection.z < 0.7f)
            {
                vecMoveSpeed.z *= 0.3f;
            }

            if (!physicalFlags.bDisableCollisionForce)
            {
                bool bUpdateTurnSpeed = m_nType != ENTITY_TYPE_VEHICLE || !CWorld::bNoMoreCollisionTorque;
                ApplyForce(vecMoveSpeed, vecDistanceToPoint, bUpdateTurnSpeed);
            }

            float fCollisionImpact1 = damageIntensity / fCollisionMass;
            AudioEngine.ReportCollision(this, entity, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
            return true;
        }
    }
    return false;
}

// 0x543890
bool CPhysical::ApplySoftCollision(CEntity* entity, CColPoint& colPoint, float& damageIntensity)
{
    if (physicalFlags.bDisableTurnForce)
    {
        ApplyCollision(entity, colPoint, damageIntensity);
    }

    CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
    CVector vecSpeed = GetSpeed(vecDistanceToPointFromThis);

    CVector vecMoveDirection = colPoint.m_vecNormal;

    float fSoftColSpeedMult = CPhysical::SOFTCOL_SPEED_MULT;

    auto* thisVehicle = static_cast<CVehicle*>(this);
    if (m_nType == ENTITY_TYPE_VEHICLE && thisVehicle->m_vehicleSubType == VEHICLE_MTRUCK)
    {
        float fForwardsDotProduct = DotProduct(&vecMoveDirection, &GetUp());
        if (fForwardsDotProduct < -0.9f)
        {
            return false;
        }

        if (fForwardsDotProduct < 0.0f)
        {
            vecMoveDirection -= fForwardsDotProduct * GetUp();
            vecMoveDirection.Normalise();
        }
        else if (fForwardsDotProduct > 0.5f)
        {
            fSoftColSpeedMult = CPhysical::SOFTCOL_SPEED_MULT2;
        }
    }

    float fSpeedDotProduct = DotProduct(&vecSpeed, &vecMoveDirection);
    CVector vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);

    if (physicalFlags.bInfiniteMass)
    {
        vecCentreOfMassMultiplied = CVector(0.0f, 0.0f, 0.0f);
    }

    CVector vecDifference = vecDistanceToPointFromThis - vecCentreOfMassMultiplied;
    CVector vecSpeedCrossProduct;
    vecSpeedCrossProduct.Cross(vecDifference, vecMoveDirection);
    float fSquaredMagnitude = vecMoveDirection.SquaredMagnitude();
    float fCollisionMass = 1.0f / (fSquaredMagnitude / m_fTurnMass + 1.0f / m_fMass);

    if (m_nType != ENTITY_TYPE_VEHICLE || thisVehicle->m_vehicleSubType
        || colPoint.m_nPieceTypeA < 13u || colPoint.m_nPieceTypeA > 16u)
    {
        float fDepth = CPhysical::SOFTCOL_DEPTH_MIN;
        if (CPhysical::SOFTCOL_DEPTH_MIN >= colPoint.m_fDepth)
        {
            fDepth = colPoint.m_fDepth;
        }

        damageIntensity = fDepth * CTimer::GetTimeStep() * CPhysical::SOFTCOL_DEPTH_MULT * fCollisionMass * 0.008f;
        if (fSpeedDotProduct >= 0.0f)
        {
            damageIntensity = 0.0f;
            return false;
        }
        damageIntensity -= fCollisionMass * fSpeedDotProduct * fSoftColSpeedMult;
    }
    else
    {
        damageIntensity = colPoint.m_fDepth * CTimer::GetTimeStep() * CPhysical::SOFTCOL_DEPTH_MULT * fCollisionMass * 0.008f;
        if (fSpeedDotProduct < 0.0f)
        {
            damageIntensity -= CPhysical::SOFTCOL_CARLINE_SPEED_MULT * fCollisionMass * fSpeedDotProduct;
        }

        float fRightDotProduct = DotProduct(&vecMoveDirection, &GetRight());
        vecMoveDirection -= 0.9f * fRightDotProduct * GetRight();
    }

    if (damageIntensity == 0.0f)
    {
        return false;
    }

    ApplyForce(vecMoveDirection * damageIntensity, vecDistanceToPointFromThis, true);
    if (damageIntensity < 0.0f)
    {
        damageIntensity *= -1.0f;
    }
    return true;
}

// 0x543C90
bool CPhysical::ApplySpringCollision(float fSuspensionForceLevel, CVector& direction, CVector& collisionPoint, float fSpringLength, float fSuspensionBias, float& fSpringForceDampingLimit) {
    float fSpringStress = 1.0f - fSpringLength;
    if (fSpringStress <= 0.0f)
        return true;

    float fTimeStep = CTimer::GetTimeStep();
    if (CTimer::GetTimeStep() >= 3.0f)
        fTimeStep = 3.0f;

    fSpringForceDampingLimit = fSpringStress * m_fMass * fSuspensionForceLevel * 0.016f * fTimeStep * fSuspensionBias;
    ApplyForce((-1.0f * fSpringForceDampingLimit) * direction, collisionPoint, true);
    return true;
}

// 0x543D60
bool CPhysical::ApplySpringCollisionAlt(float fSuspensionForceLevel, CVector& direction, CVector& collisionPoint, float fSpringLength, float fSuspensionBias, CVector& normal, float& fSpringForceDampingLimit) {
    float fSpringStress = 1.0f - fSpringLength;
    if (fSpringStress <= 0.0f)
        return true;

    if (DotProduct(direction, normal) > 0.0f)
        normal *= -1.0f;

    float fTimeStep = CTimer::GetTimeStep();
    if (CTimer::GetTimeStep() >= 3.0f)
        fTimeStep = 3.0f;

    fSpringForceDampingLimit = fSpringStress * (fTimeStep * m_fMass) * fSuspensionForceLevel * fSuspensionBias * 0.016f;
    if (physicalFlags.bMakeMassTwiceAsBig)
        fSpringForceDampingLimit *= 0.75f;

    ApplyForce(fSpringForceDampingLimit * normal, collisionPoint, true);
    return true;
}

// 0x543E90
bool CPhysical::ApplySpringDampening(float fDampingForce, float fSpringForceDampingLimit, CVector& direction, CVector& collisionPoint, CVector& collisionPos) {
    float fCollisionPosDotProduct = DotProduct(collisionPos, direction);
    CVector vecCollisionPointSpeed = GetSpeed(collisionPoint);
    float fCollisionPointSpeedDotProduct = DotProduct(vecCollisionPointSpeed, direction);
    float fTimeStep = CTimer::GetTimeStep();
    if (CTimer::GetTimeStep() >= 3.0f)
        fTimeStep = 3.0f;

    float fDampingForceTimeStep = fTimeStep * fDampingForce;
    if (physicalFlags.bMakeMassTwiceAsBig)
        fDampingForceTimeStep *= 2.0f;

    fDampingForceTimeStep = clamp<float>(fDampingForceTimeStep, -DAMPING_LIMIT_IN_FRAME, DAMPING_LIMIT_IN_FRAME);
    float fDampingSpeed = -(fDampingForceTimeStep * fCollisionPosDotProduct);
    if (fDampingSpeed > 0.0 && fDampingSpeed + fCollisionPointSpeedDotProduct > 0.0f) {
        if (fCollisionPointSpeedDotProduct >= 0.0f)
            fDampingSpeed = 0.0f;
        else
            fDampingSpeed = -fCollisionPointSpeedDotProduct;
    }
    else if (fDampingSpeed < 0.0f && fDampingSpeed + fCollisionPointSpeedDotProduct < 0.0f) {
        if (fCollisionPointSpeedDotProduct <= 0.0f)
            fDampingSpeed = 0.0f;
        else
            fDampingSpeed = -fCollisionPointSpeedDotProduct;
    }

    CVector center = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
    CVector distance = collisionPoint - center;
    float fSpringForceDamping = GetMass(distance, direction) * fDampingSpeed;
    fSpringForceDampingLimit = fabs(fSpringForceDampingLimit) * DAMPING_LIMIT_OF_SPRING_FORCE;
    if (fSpringForceDamping > fSpringForceDampingLimit)
        fSpringForceDamping = fSpringForceDampingLimit;
    ApplyForce(fSpringForceDamping * direction, collisionPoint, true);
    return true;
}

// Unused
bool CPhysical::ApplySpringDampeningOld(float arg0, float arg1, CVector& arg2, CVector& arg3, CVector& arg4)
{
    return ((bool(__thiscall*)(CPhysical*, float, float, CVector&, CVector&, CVector&))0x544100)(this, arg0, arg1, arg2, arg3, arg4);
}

// 0x544280
void CPhysical::RemoveRefsToEntity(CEntity* entity)
{
    uint8 collidedEntityIndex = m_nNumEntitiesCollided;
    while (collidedEntityIndex < m_nNumEntitiesCollided); {
        if (m_apCollidedEntities[collidedEntityIndex] == entity) {
            for (uint16 i = collidedEntityIndex; i < m_nNumEntitiesCollided - 1; ++i) {
                m_apCollidedEntities[i] = m_apCollidedEntities[i + 1];
            }
            m_nNumEntitiesCollided--;
        }
        else {
            collidedEntityIndex++;
        }
    }
}

// 0x5442F0
void CPhysical::DettachEntityFromEntity(float x, float y, float z, bool bApplyTurnForce)
{
    CMatrix vecDetachOffsetMatrix;
    if (m_nType == ENTITY_TYPE_VEHICLE && m_pAttachedTo && m_pAttachedTo->m_nType == ENTITY_TYPE_VEHICLE) {
        CColModel* colModel = CEntity::GetColModel();
        CCollisionData* colData = colModel->m_pColData;
        if (colData) {
            uint8 nNumLines = colData->m_nNumLines;
            colData->m_nNumLines = 0;
            CColModel* attachedToColModel = m_pAttachedTo->GetColModel();
            CMatrix& attachedToMatrix = m_pAttachedTo->GetMatrix();
            if (CCollision::ProcessColModels(*m_matrix, *colModel, attachedToMatrix, *attachedToColModel, CWorld::m_aTempColPts, nullptr, nullptr, false))
                m_pEntityIgnoredCollision = m_pAttachedTo;
            else if (m_pEntityIgnoredCollision == m_pAttachedTo)
                m_pEntityIgnoredCollision = nullptr;
            colData->m_nNumLines = nNumLines;
        }
        else if (m_pEntityIgnoredCollision == m_pAttachedTo) {
            m_pEntityIgnoredCollision = nullptr;
        }
    }
    else {
        m_pEntityIgnoredCollision = m_pAttachedTo;
    }

    vecDetachOffsetMatrix.ResetOrientation();
    vecDetachOffsetMatrix.RotateZ(y);
    vecDetachOffsetMatrix.RotateX(x);

    vecDetachOffsetMatrix *= m_pAttachedTo->GetMatrix();
    CVector vecForce = vecDetachOffsetMatrix.GetForward() * z;
    CWorld::Remove(this);
    SetIsStatic(false);
    physicalFlags.bAttachedToEntity = false;
    CWorld::Add(this);
    if (physicalFlags.bDisableCollisionForce) {
        auto* thisObject = static_cast<CObject*>(this);
        CObjectData* pThisObjectInfo = thisObject->m_pObjectInfo;
        if (m_nType != ENTITY_TYPE_OBJECT || pThisObjectInfo->m_fMass >= 99998.0f)
        {
            physicalFlags.bCollidable = true;
            ResetTurnSpeed();
            ResetMoveSpeed();
            bApplyTurnForce = false;
        }
        else
        {
            physicalFlags.bDisableCollisionForce = false;
            m_fMass = pThisObjectInfo->m_fMass;
            m_fTurnMass = pThisObjectInfo->m_fTurnMass;
        }
    }

    if (!physicalFlags.bDisableCollisionForce) {
        if (m_pAttachedTo->m_nType > ENTITY_TYPE_BUILDING && m_pAttachedTo->m_nType < ENTITY_TYPE_DUMMY) {
            m_vecMoveSpeed = m_pAttachedTo->m_vecMoveSpeed;
            m_vecMoveSpeed += vecForce;
        }
    }

    if (bApplyTurnForce)
        ApplyTurnForce(vecForce, vecForce * 0.5f);

    m_pAttachedTo = nullptr;
    m_qAttachedEntityRotation.real = 0.0f;
    m_qAttachedEntityRotation.imag = CVector(0.0f, 0.0f, 0.0f);
    m_vecAttachOffset = CVector(0.0f, 0.0f, 0.0f);
}

// 0x5446A0
void CPhysical::DettachAutoAttachedEntity()
{
    SetIsStatic(false);
    physicalFlags.bAttachedToEntity = false;
    m_nFakePhysics = 0;
    if (!physicalFlags.bDisableCollisionForce) {
        if (m_pAttachedTo->m_nType == ENTITY_TYPE_VEHICLE) {
            m_vecMoveSpeed = m_pAttachedTo->m_vecMoveSpeed;
            m_vecTurnSpeed = m_pAttachedTo->m_vecTurnSpeed;
        }
    }
    else
    {
        physicalFlags.bCollidable = true;
        ResetTurnSpeed();
        ResetMoveSpeed();
    }
    m_vecAttachOffset = CVector(0.0f, 0.0f, 0.0f);
    m_pEntityIgnoredCollision = nullptr;
    m_pAttachedTo = nullptr;
    m_qAttachedEntityRotation.real = 0.0f;
    m_qAttachedEntityRotation.imag = CVector(0.0f, 0.0f, 0.0f);
    if (m_nType == ENTITY_TYPE_OBJECT) {
        auto* object = static_cast<CObject*>(this);
        m_fElasticity = object->m_pObjectInfo->m_fElasticity;
    }
}

// 0x5447B0
float CPhysical::GetLightingFromCol(bool bInteriorLighting)
{
    float fAmbientRedBlue = CTimeCycle::GetAmbientRed_BeforeBrightness() + CTimeCycle::GetAmbientBlue_BeforeBrightness();
    float fLighting = (CTimeCycle::GetAmbientGreen_BeforeBrightness() + fAmbientRedBlue) * 0.33333f + m_fContactSurfaceBrightness;
    if (!bInteriorLighting) {
        fLighting *= (CTimeCycle::SumOfCurrentRGB1() * (1.0f / 765.0f) * TEST_ADD_AMBIENT_LIGHT_FRAC + 1.0f - TEST_ADD_AMBIENT_LIGHT_FRAC)
                    + CTimeCycle::SumOfCurrentRGB2() * (1.0f / 765.0f)  * TEST_ADD_AMBIENT_LIGHT_FRAC;
    }
    return fLighting;
}

// 0x544850
float CPhysical::GetLightingTotal()
{
    bool bInteriorLighting = false;
    if (m_nAreaCode)
        bInteriorLighting = true;

    if (m_nType  == ENTITY_TYPE_PED) {
        CPed* ped = static_cast<CPed*>(this);
        if (ped->m_pPlayerData && (CGame::currArea || ped->m_pPlayerData->m_bForceInteriorLighting))
            bInteriorLighting = true;
    }
    return GetLightingFromCol(bInteriorLighting) + m_fDynamicLighting;
}

// 0x5448B0
bool CPhysical::CanPhysicalBeDamaged(eWeaponType weapon, bool* bDamagedDueToFireOrExplosionOrBullet)
{
    if (bDamagedDueToFireOrExplosionOrBullet)
        *bDamagedDueToFireOrExplosionOrBullet = false;

    switch (weapon)
    {
    case WEAPON_UNARMED:
    case WEAPON_BRASSKNUCKLE:
    case WEAPON_GOLFCLUB:
    case WEAPON_NIGHTSTICK:
    case WEAPON_KNIFE:
    case WEAPON_BASEBALLBAT:
    case WEAPON_SHOVEL:
    case WEAPON_POOL_CUE:
    case WEAPON_KATANA:
    case WEAPON_CHAINSAW:
    case WEAPON_DILDO1:
    case WEAPON_DILDO2:
    case WEAPON_VIBE1:
    case WEAPON_VIBE2:
    case WEAPON_FLOWERS:
    case WEAPON_CANE:
        if (!physicalFlags.bMeeleProof)
            return true;
        return false;
    case WEAPON_GRENADE:
    case WEAPON_ROCKET:
    case WEAPON_ROCKET_HS:
    case WEAPON_FREEFALL_BOMB:
    case WEAPON_RLAUNCHER:
    case WEAPON_RLAUNCHER_HS:
    case WEAPON_REMOTE_SATCHEL_CHARGE:
    case WEAPON_DETONATOR:
    case WEAPON_ARMOUR | WEAPON_NIGHTSTICK:
        if (!physicalFlags.bExplosionProof)
            break;
        return false;
    case WEAPON_TEARGAS:
    case WEAPON_SPRAYCAN:
    case WEAPON_EXTINGUISHER:
    case WEAPON_CAMERA:
    case WEAPON_NIGHTVISION:
    case WEAPON_INFRARED:
    case WEAPON_PARACHUTE:
    case WEAPON_LAST_WEAPON:
    case WEAPON_ARMOUR:
    case WEAPON_ARMOUR | WEAPON_BASEBALLBAT:
        return true;
    case WEAPON_MOLOTOV:
        if (!physicalFlags.bFireProof)
            break;
        return false;
    case WEAPON_PISTOL:
    case WEAPON_PISTOL_SILENCED:
    case WEAPON_DESERT_EAGLE:
    case WEAPON_SHOTGUN:
    case WEAPON_SAWNOFF_SHOTGUN:
    case WEAPON_SPAS12_SHOTGUN:
    case WEAPON_MICRO_UZI:
    case WEAPON_MP5:
    case WEAPON_AK47:
    case WEAPON_M4:
    case WEAPON_TEC9:
    case WEAPON_COUNTRYRIFLE:
    case WEAPON_SNIPERRIFLE:
    case WEAPON_MINIGUN:
    case WEAPON_ARMOUR | WEAPON_KNIFE:
        if (physicalFlags.bBulletProof)
            return false;
        break;
    case WEAPON_FLAMETHROWER:
        if (!physicalFlags.bFireProof)
            return true;
        return false;
    case WEAPON_ARMOUR | WEAPON_BRASSKNUCKLE:
    case WEAPON_ARMOUR | WEAPON_GOLFCLUB:
    case WEAPON_ARMOUR | WEAPON_SHOVEL:
        if (physicalFlags.bCollisionProof)
            return false;
        return true;
    }

    if (!bDamagedDueToFireOrExplosionOrBullet)
        return true;
    *bDamagedDueToFireOrExplosionOrBullet = true;
    return true;
}

// 0x544C40
void CPhysical::ApplyAirResistance()
{
    if (m_fAirResistance <= 0.1f || m_nType  == ENTITY_TYPE_VEHICLE)
    {
        float fSpeedMagnitude = m_vecMoveSpeed.Magnitude() * m_fAirResistance;
        if (CCullZones::DoExtraAirResistanceForPlayer())
        {
            if (m_nType == ENTITY_TYPE_VEHICLE)
            {
                auto* vehicle = static_cast<CVehicle*>(this);
                if (!vehicle->m_vehicleSubType || vehicle->m_vehicleSubType == VEHICLE_BIKE)
                    fSpeedMagnitude = CVehicle::m_fAirResistanceMult * fSpeedMagnitude;
            }
        }

        m_vecMoveSpeed *= pow(1.0f - fSpeedMagnitude, CTimer::GetTimeStep());
        m_vecTurnSpeed *= 0.99f;
    }
    else
    {
        float fAirResistanceTimeStep = pow(m_fAirResistance, CTimer::GetTimeStep());
        m_vecMoveSpeed *= fAirResistanceTimeStep;
        m_vecTurnSpeed *= fAirResistanceTimeStep;
    }
}

// 0x544D50
bool CPhysical::ApplyCollisionAlt(CPhysical* entity, CColPoint& colPoint, float& damageIntensity, CVector& outVecMoveSpeed, CVector& outVecTurnSpeed)
{
    if (m_pAttachedTo)
    {
        if (m_pAttachedTo->m_nType > ENTITY_TYPE_BUILDING && m_pAttachedTo->m_nType < ENTITY_TYPE_DUMMY
            && m_pAttachedTo->m_nType != ENTITY_TYPE_PED)
        {
            float fDamageIntensity = 0.0f;
            m_pAttachedTo->ApplySoftCollision(entity, colPoint, fDamageIntensity);
        }
    }

    if (physicalFlags.bDisableTurnForce)
    {
        float fSpeedDotProduct = DotProduct(&m_vecMoveSpeed, &colPoint.m_vecNormal);
        if (fSpeedDotProduct < 0.0f)
        {
            damageIntensity = -(fSpeedDotProduct * m_fMass);
            ApplyMoveForce(colPoint.m_vecNormal * damageIntensity);

            float fCollisionImpact1 = damageIntensity / m_fMass;
            AudioEngine.ReportCollision(
                this,
                entity,
                colPoint.m_nSurfaceTypeA,
                colPoint.m_nSurfaceTypeB,
                colPoint.m_vecPoint,
                &colPoint.m_vecNormal,
                fCollisionImpact1,
                1.0f,
                false,
                false
            );
            return true;
        }
        return false;
    }

    auto* vehicle = static_cast<CVehicle*>(this);
    CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
    CVector vecSpeed = GetSpeed(vecDistanceToPointFromThis);

    if (physicalFlags.bAddMovingCollisionSpeed && m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeA == SURFACE_CAR_MOVINGCOMPONENT)
        vecSpeed += vehicle->AddMovingCollisionSpeed(vecDistanceToPointFromThis);

    CVector vecMoveDirection = colPoint.m_vecNormal;
    float fSpeedDotProduct = DotProduct(&vecMoveDirection, &vecSpeed);
    if (fSpeedDotProduct >= 0.0f)
    {
        return false;
    }

    CVector vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
    if (physicalFlags.bInfiniteMass)
    {
        vecCentreOfMassMultiplied = CVector(0.0f, 0.0f, 0.0f);
    }

    CVector vecDifference = vecDistanceToPointFromThis - vecCentreOfMassMultiplied;
    CVector vecCrossProduct;
    vecCrossProduct.Cross(vecDifference, vecMoveDirection);
    float fSquaredMagnitude = vecCrossProduct.SquaredMagnitude();
    float fCollisionMass = 1.0f / (fSquaredMagnitude / m_fTurnMass + 1.0f / m_fMass);

    uint16 entityAltCol = ALT_ENITY_COL_DEFAULT;
    float fMoveSpeedLimit = CTimer::GetTimeStep() * 0.008f;
    if (m_nType == ENTITY_TYPE_OBJECT)
    {
        entityAltCol = ALT_ENITY_COL_OBJECT;
        fMoveSpeedLimit *= 1.3f;
    }
    else
    {
        if (m_nType == ENTITY_TYPE_VEHICLE && !physicalFlags.bSubmergedInWater) {
            float fMoveSpeedLimitMultiplier = 0.0f;
            uint32 vehicleClass = vehicle->m_vehicleType;
            if (vehicleClass != VEHICLE_BIKE || (m_nStatus != STATUS_ABANDONED) && m_nStatus != STATUS_WRECKED)
            {
                if (vehicleClass == VEHICLE_BOAT)
                {
                    fMoveSpeedLimitMultiplier = 1.5f;
                    entityAltCol = ALT_ENITY_COL_BOAT;
                }
                else
                {
                    if (GetUp().z < -0.3f)
                    {
                        fMoveSpeedLimitMultiplier = 1.4f;
                        entityAltCol = ALT_ENITY_COL_VEHICLE;
                    }
                }
            }
            else
            {
                fMoveSpeedLimitMultiplier = 1.7f;
                entityAltCol = ALT_ENITY_COL_BIKE_WRECKED;
            }
            fMoveSpeedLimit *= fMoveSpeedLimitMultiplier;
        }
    }

    float fCollisionImpact2 = 1.0f;
    bool bUseElasticity = false;
    if (entityAltCol == ALT_ENITY_COL_OBJECT)
    {
        if (!m_bHasContacted
            && fabs(m_vecMoveSpeed.x) < fMoveSpeedLimit
            && fabs(m_vecMoveSpeed.y) < fMoveSpeedLimit
            && fMoveSpeedLimit + fMoveSpeedLimit > fabs(m_vecMoveSpeed.z))
        {
            fCollisionImpact2 = 0.0f;
            damageIntensity = -0.98f * fCollisionMass * fSpeedDotProduct;
        }
        bUseElasticity = true;
    }
    else
    {
        if (entityAltCol != ALT_ENITY_COL_BIKE_WRECKED)
        {
            if (entityAltCol == ALT_ENITY_COL_VEHICLE)
            {
                if (fabs(m_vecMoveSpeed.x) < fMoveSpeedLimit
                    && fabs(m_vecMoveSpeed.y) < fMoveSpeedLimit
                    && fMoveSpeedLimit + fMoveSpeedLimit > fabs(m_vecMoveSpeed.z))
                {
                    damageIntensity = damageIntensity;
                    fCollisionImpact2 = 0.0f;
                    damageIntensity = -0.95f * fCollisionMass * fSpeedDotProduct;
                }
                else
                {
                    bUseElasticity = true;
                }
            }
            else if (entityAltCol == ALT_ENITY_COL_BOAT
                && fabs(m_vecMoveSpeed.x) < fMoveSpeedLimit
                && fabs(m_vecMoveSpeed.y) < fMoveSpeedLimit
                && fMoveSpeedLimit + fMoveSpeedLimit > fabs(m_vecMoveSpeed.z))
            {
                fCollisionImpact2 = 0.0f;
                damageIntensity = -0.95f * fCollisionMass * fSpeedDotProduct;
            }
            else
            {
                bUseElasticity = true;
            }
        }
        else
        {
            if (fabs(m_vecMoveSpeed.x) >= fMoveSpeedLimit
                || fabs(m_vecMoveSpeed.y) >= fMoveSpeedLimit
                || fMoveSpeedLimit + fMoveSpeedLimit <= fabs(m_vecMoveSpeed.z))
            {
                bUseElasticity = true;
            }
            else
            {
                fCollisionImpact2 = 0.0f;
                damageIntensity = -0.95f * fCollisionMass * fSpeedDotProduct;
            }
        }
    }

    if (bUseElasticity)
    {
        float fElasticity = m_fElasticity + m_fElasticity;
        if (m_nType != ENTITY_TYPE_VEHICLE || vehicle->m_vehicleType != VEHICLE_BOAT
            || colPoint.m_nSurfaceTypeB != SURFACE_WOOD_SOLID && vecMoveDirection.z >= 0.5f)
        {
            fElasticity = m_fElasticity;
        }

        damageIntensity = -((fElasticity + 1.0f) * fCollisionMass * fSpeedDotProduct);
    }

    CVector vecMoveSpeed = vecMoveDirection * damageIntensity;

    if (physicalFlags.bDisableZ || physicalFlags.bInfiniteMass || physicalFlags.bDisableMoveForce)
    {
        ApplyForce(vecMoveSpeed, vecDistanceToPointFromThis, true);
    }
    else
    {
        CVector vecSpeed = vecMoveSpeed / m_fMass;
        if (m_nType == ENTITY_TYPE_VEHICLE)
        {
            if (!m_bHasHitWall || m_vecMoveSpeed.SquaredMagnitude() <= 0.1f
                && (entity->m_nType == ENTITY_TYPE_BUILDING || entity->physicalFlags.bDisableCollisionForce))
            {
                outVecMoveSpeed += vecSpeed * 1.2f;
            }
            else
            {
                outVecMoveSpeed += vecSpeed;
            }

            vecMoveSpeed *= 0.8f;
        }
        else
        {
            outVecMoveSpeed += vecSpeed;
        }

        vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
        float fTurnMass = m_fTurnMass;
        CVector vecDifference = vecDistanceToPointFromThis - vecCentreOfMassMultiplied;
        CVector vecCrossProduct;
        vecCrossProduct.Cross(vecDifference, vecMoveSpeed);
        outVecTurnSpeed += vecCrossProduct / fTurnMass;
    }

    float fCollisionImpact1 = damageIntensity / fCollisionMass;
    AudioEngine.ReportCollision(
        this,
        entity,
        colPoint.m_nSurfaceTypeA,
        colPoint.m_nSurfaceTypeB,
        colPoint.m_vecPoint,
        &colPoint.m_vecNormal,
        fCollisionImpact1,
        fCollisionImpact2,
        false,
        false
    );
    return true;
}

// 0x5454C0
bool CPhysical::ApplyFriction(float fFriction, CColPoint& colPoint)
{
    if (physicalFlags.bDisableCollisionForce)
    {
        return false;
    }

    if (physicalFlags.bDisableTurnForce)
    {
        float fMoveSpeedDotProduct = DotProduct(&m_vecMoveSpeed, &colPoint.m_vecNormal);
        CVector vecSpeedDifference = m_vecMoveSpeed - (fMoveSpeedDotProduct * colPoint.m_vecNormal);
        float fMoveSpeedMagnitude = vecSpeedDifference.Magnitude();
        if (fMoveSpeedMagnitude > 0.0f)
        {
            CVector vecMoveDirection = vecSpeedDifference / fMoveSpeedMagnitude;

            float fSpeed = -fMoveSpeedMagnitude;
            float fForce = -(CTimer::GetTimeStep() / m_fMass * fFriction);
            if (fSpeed < fForce)
            {
                fSpeed = fForce;
            }

            m_vecFrictionMoveSpeed.x += vecMoveDirection.x * fSpeed;
            m_vecFrictionMoveSpeed.y += vecMoveDirection.y * fSpeed;
            return true;
        }
        return false;
    }

    CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
    CVector vecSpeed = GetSpeed(vecDistanceToPointFromThis);

    float fMoveSpeedDotProduct = DotProduct(&vecSpeed, &colPoint.m_vecNormal);
    CVector vecSpeedDifference = vecSpeed - (fMoveSpeedDotProduct * colPoint.m_vecNormal);

    float fMoveSpeedMagnitude = vecSpeedDifference.Magnitude();
    if (fMoveSpeedMagnitude <= 0.0f)
    {
        return false;
    }

    CVector vecMoveDirection = vecSpeedDifference / fMoveSpeedMagnitude;

    CVector vecCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
    CVector vecDifference = vecDistanceToPointFromThis - vecCentreOfMassMultiplied;
    CVector vecSpeedCrossProduct;
    vecSpeedCrossProduct.Cross(vecDifference, vecMoveDirection);
    float squaredMagnitude = vecSpeedCrossProduct.SquaredMagnitude();
    float fCollisionMass = -(1.0f / (squaredMagnitude / m_fTurnMass + 1.0f / m_fMass) * fMoveSpeedMagnitude);
    float fNegativeFriction = -fFriction;
    if (fCollisionMass < fNegativeFriction)
    {
        fCollisionMass = fNegativeFriction;
    }

    ApplyFrictionForce(vecMoveDirection * fCollisionMass, vecDistanceToPointFromThis);

    auto* vehicle = static_cast<CVehicle*>(this);
    if (fMoveSpeedMagnitude > 0.1f
        && g_surfaceInfos->GetFrictionEffect(colPoint.m_nSurfaceTypeB)
        && (g_surfaceInfos->GetFrictionEffect(colPoint.m_nSurfaceTypeA) == FRICTION_EFFECT_SPARKS || m_nType == ENTITY_TYPE_VEHICLE)
        && (m_nType != ENTITY_TYPE_VEHICLE || vehicle->m_vehicleSubType != VEHICLE_BMX || !vehicle->m_pDriver
            || fabs(DotProduct(&colPoint.m_vecNormal, &GetRight())) >= 0.86669999f))
    {

        CVector across = vecMoveDirection * (fMoveSpeedMagnitude * 0.25f);
        CVector direction = vecMoveDirection + (colPoint.m_vecNormal * 0.1f);
        CVector vecSpeedCrossProduct;
        vecSpeedCrossProduct.Cross(colPoint.m_vecNormal, m_vecMoveSpeed);
        vecSpeedCrossProduct.Normalise();

        for (int32 i = 0; i < 8; i++)
        {
            float fRandom = CGeneral::GetRandomNumberInRange(-0.2f, 0.2f);
            CVector origin = colPoint.m_vecPoint + (vecSpeedCrossProduct * fRandom);
            float force = fMoveSpeedMagnitude * 12.5f;
            g_fx.AddSparks(origin, direction, force, 1, across, SPARK_PARTICLE_SPARK2, 0.1f, 1.0f);
        }
    }
    return true;
}

// 0x545980
bool CPhysical::ApplyFriction(CPhysical* entity, float fFriction, CColPoint& colPoint)
{
    if (physicalFlags.bDisableTurnForce && entity->physicalFlags.bDisableTurnForce)
    {
        float fThisSpeedDotProduct = DotProduct(&m_vecMoveSpeed, &colPoint.m_vecNormal);
        float fEntitySpeedDotProduct = DotProduct(&entity->m_vecMoveSpeed, &colPoint.m_vecNormal);

        CVector vecThisSpeedDifference = m_vecMoveSpeed - (fThisSpeedDotProduct * colPoint.m_vecNormal);
        CVector vecEntitySpeedDifference = entity->m_vecMoveSpeed - (fEntitySpeedDotProduct * colPoint.m_vecNormal);

        float fThisSpeedMagnitude = vecThisSpeedDifference.Magnitude();
        float fEntitySpeedMagnitude = vecEntitySpeedDifference.Magnitude();

        float fEntityMass = entity->m_fMass;
        float fThisMass = m_fMass;

        CVector vecMoveDirection = vecThisSpeedDifference / fThisSpeedMagnitude;
        float fSpeed = (fEntityMass * fEntitySpeedMagnitude + fThisMass * fThisSpeedMagnitude) / (fEntityMass + fThisMass);
        if (fThisSpeedMagnitude > fSpeed) {
            float fThisSpeed = fThisMass * (fSpeed - fThisSpeedMagnitude);
            float fEntitySpeed = fEntityMass * (fSpeed - fEntitySpeedMagnitude);
            float fFrictionTimeStep = -(CTimer::GetTimeStep() * fFriction);
            if (fThisSpeed < fFrictionTimeStep)
            {
                fThisSpeed = fFrictionTimeStep;
            }

            // BUG: Both if conditions are the same.
            if (fThisSpeed < fFrictionTimeStep)
            {
                fThisSpeed = fFrictionTimeStep;
            }

            ApplyFrictionMoveForce(vecMoveDirection * fThisSpeed);
            entity->ApplyFrictionMoveForce(vecMoveDirection * fEntitySpeed);
            return true;
        }
        return false;
    }

    if (physicalFlags.bDisableTurnForce)
    {
        if (entity->m_nType == ENTITY_TYPE_VEHICLE)
        {
            return false;
        }

        CVector vecDistanceToPoint = colPoint.m_vecPoint - entity->GetPosition();
        CVector vecEntitySpeed = entity->GetSpeed(vecDistanceToPoint);

        float fThisSpeedDotProduct = DotProduct(&m_vecMoveSpeed, &colPoint.m_vecNormal);
        float fEntitySpeedDotProduct = DotProduct(&vecEntitySpeed, &colPoint.m_vecNormal);

        CVector vecThisSpeedDifference = m_vecMoveSpeed - (fThisSpeedDotProduct * colPoint.m_vecNormal);
        CVector vecEntitySpeedDifference = vecEntitySpeed - (fEntitySpeedDotProduct * colPoint.m_vecNormal);

        float fThisSpeedMagnitude = vecThisSpeedDifference.Magnitude();
        float fEntitySpeedMagnitude = vecEntitySpeedDifference.Magnitude();

        CVector vecMoveDirection = vecThisSpeedDifference * (1.0f / fThisSpeedMagnitude);
        CVector vecEntityCentreOfMassMultiplied = Multiply3x3(entity->GetMatrix(), entity->m_vecCentreOfMass);
        CVector vecEntityDifference = vecDistanceToPoint - vecEntityCentreOfMassMultiplied;
        CVector vecEntitySpeedCrossProduct;
        vecEntitySpeedCrossProduct.Cross(vecEntityDifference, vecMoveDirection);
        float squaredMagnitude = vecEntitySpeedCrossProduct.SquaredMagnitude();
        float fEntityCollisionMass = 1.0f / ((squaredMagnitude) / entity->m_fTurnMass + 1.0f / entity->m_fMass);
        float fThisMass = m_fMass;
        float fSpeed = (fEntitySpeedMagnitude * fEntityCollisionMass + fThisMass * fThisSpeedMagnitude) / (fEntityCollisionMass + fThisMass);
        if (fThisSpeedMagnitude > fSpeed) {
            float fThisSpeed = fThisMass * (fSpeed - fThisSpeedMagnitude);
            float fEntitySpeed = fEntityCollisionMass * (fSpeed - fEntitySpeedMagnitude);
            float fFrictionTimeStep = CTimer::GetTimeStep() * fFriction;
            float fFrictionTimeStepNegative = -fFrictionTimeStep;
            if (fThisSpeed < fFrictionTimeStepNegative)
            {
                fThisSpeed = fFrictionTimeStepNegative;
            }

            if (fEntitySpeed > fFrictionTimeStep)
            {
                fEntitySpeed = fFrictionTimeStep;
            }

            ApplyFrictionMoveForce(vecMoveDirection * fThisSpeed);
            if (!entity->physicalFlags.bDisableCollisionForce)
            {
                entity->ApplyFrictionForce(vecMoveDirection * fEntitySpeed, vecDistanceToPoint);
                return true;
            }
            return true;
        }
        return false;
    }

    if (!entity->physicalFlags.bDisableTurnForce)
    {
        CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
        CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

        CVector vecDistanceToPoint = colPoint.m_vecPoint - entity->GetPosition();
        CVector vecEntitySpeed = entity->GetSpeed(vecDistanceToPoint);

        float fThisSpeedDotProduct = DotProduct(&vecThisSpeed, &colPoint.m_vecNormal);
        float fEntitySpeedDotProduct = DotProduct(&vecEntitySpeed, &colPoint.m_vecNormal);
        if (0.2f * 0.707f > fabs(fThisSpeedDotProduct))
        {
            fFriction = 0.05f * fFriction;
        }

        CVector vecThisSpeedDifference = vecThisSpeed - (fThisSpeedDotProduct * colPoint.m_vecNormal);
        CVector vecEntitySpeedDifference = vecEntitySpeed - (fEntitySpeedDotProduct * colPoint.m_vecNormal);

        float fThisSpeedMagnitude = vecThisSpeedDifference.Magnitude();
        float fEntitySpeedMagnitude = vecEntitySpeedDifference.Magnitude();

        CVector vecMoveDirection = vecThisSpeedDifference * (1.0f / fThisSpeedMagnitude);

        CVector vecThisCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);

        CVector vecThisDifference = vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied;
        CVector vecThisSpeedCrossProduct;
        vecThisSpeedCrossProduct.Cross(vecThisDifference, vecMoveDirection);
        float squaredMagnitude = vecThisSpeedCrossProduct.SquaredMagnitude();
        float fThisCollisionMass = 1.0f / (squaredMagnitude / m_fTurnMass + 1.0f / m_fMass);

        CVector vecEntityCentreOfMassMultiplied = Multiply3x3(entity->GetMatrix(), entity->m_vecCentreOfMass);

        CVector vecEntityDifference = vecDistanceToPoint - vecEntityCentreOfMassMultiplied;
        CVector vecEntitySpeedCrossProduct;
        vecEntitySpeedCrossProduct.Cross(vecEntityDifference, vecMoveDirection);
        squaredMagnitude = vecEntitySpeedCrossProduct.SquaredMagnitude();
        float fEntityCollisionMass = 1.0f / (squaredMagnitude / entity->m_fTurnMass + 1.0f / entity->m_fMass);
        float fSpeed = (fEntitySpeedMagnitude * fEntityCollisionMass + fThisCollisionMass * fThisSpeedMagnitude) / (fEntityCollisionMass + fThisCollisionMass);
        if (fThisSpeedMagnitude > fSpeed) {
            float fThisSpeed = fThisCollisionMass * (fSpeed - fThisSpeedMagnitude);
            float fEntitySpeed = fEntityCollisionMass * (fSpeed - fEntitySpeedMagnitude);
            float fNegativeFriction = -fFriction;
            if (fThisSpeed < fNegativeFriction) {
                fThisSpeed = fNegativeFriction;
            }

            if (fEntitySpeed > fFriction) {
                fEntitySpeed = fFriction;
            }

            if (!physicalFlags.bDisableCollisionForce) {
                ApplyFrictionForce(vecMoveDirection * fThisSpeed, vecDistanceToPointFromThis);
            }

            if (!entity->physicalFlags.bDisableCollisionForce) {
                entity->ApplyFrictionForce(vecMoveDirection * fEntitySpeed, vecDistanceToPoint);
            }
            return true;
        }
        return false;
    }

    if (m_nType == ENTITY_TYPE_VEHICLE)
    {
        return false;
    }

    CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
    CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

    float fThisSpeedDotProduct = DotProduct(&vecThisSpeed, &colPoint.m_vecNormal);
    float fEntitySpeedDotProduct = DotProduct(&entity->m_vecMoveSpeed, &colPoint.m_vecNormal);

    CVector vecThisSpeedDifference = vecThisSpeed - (fThisSpeedDotProduct * colPoint.m_vecNormal);
    CVector vecEntitySpeedDifference = entity->m_vecMoveSpeed - (fEntitySpeedDotProduct * colPoint.m_vecNormal);

    float fThisSpeedMagnitude = vecThisSpeedDifference.Magnitude();
    float fEntitySpeedMagnitude = vecEntitySpeedDifference.Magnitude();

    CVector vecMoveDirection = vecThisSpeedDifference * (1.0f / fThisSpeedMagnitude);

    CVector vecThisCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);

    CVector vecThisDifference = vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied;
    CVector vecThisSpeedCrossProduct;
    vecThisSpeedCrossProduct.Cross(vecThisDifference, vecMoveDirection);
    float squaredMagnitude = vecThisSpeedCrossProduct.SquaredMagnitude();
    float fEntityMass = entity->m_fMass;
    float fThisCollisionMass = 1.0f / (squaredMagnitude / m_fTurnMass + 1.0f / m_fMass);
    float fSpeed = (fEntityMass * fEntitySpeedMagnitude + fThisCollisionMass * fThisSpeedMagnitude) / (fEntityMass + fThisCollisionMass);
    if (fThisSpeedMagnitude > fSpeed) {
        float fThisSpeed = (fSpeed - fThisSpeedMagnitude) * fThisCollisionMass;
        float fEntitySpeed = (fSpeed - fEntitySpeedMagnitude) * fEntityMass;
        float fFrictionTimeStep = CTimer::GetTimeStep() * fFriction;
        float fNegativeFrictionTimeStep = -fFrictionTimeStep;
        if (fThisSpeed < fNegativeFrictionTimeStep) {
            fThisSpeed = fNegativeFrictionTimeStep;
        }

        if (fEntitySpeed > fFrictionTimeStep) {
            fEntitySpeed = fFrictionTimeStep;
        }

        if (!physicalFlags.bDisableCollisionForce) {
            ApplyFrictionForce(vecMoveDirection * fThisSpeed, vecDistanceToPointFromThis);
        }

        entity->ApplyFrictionMoveForce(vecMoveDirection * fEntitySpeed);
        return true;
    }
    return false;
}

// 0x546670
bool CPhysical::ProcessShiftSectorList(int32 sectorX, int32 sectorY)
{
    CBaseModelInfo* pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    float fBoundingSphereRadius = pModelInfo->GetColModel()->GetBoundRadius();
    float fMaxColPointDepth = 0.0f;
    CVector vecShift;
    CColPoint colPoints[32];
    CVector vecBoundCentre;

    GetBoundCentre(&vecBoundCentre);

    CSector* sector = GetSector(sectorX, sectorY);
    CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);

    int32 totalAcceptableColPoints = 0;
    int32 scanListIndex = 4;
    do
    {
        CPtrListDoubleLink* doubleLinkList = nullptr;
        switch (--scanListIndex)
        {
        case 0:
            doubleLinkList = &sector->m_buildings;
            break;
        case 1:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_VEHICLES];
            break;
        case 2:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_PEDS];
            break;
        case 3:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_OBJECTS];
            break;
        }
        CPtrNodeDoubleLink* node = doubleLinkList->GetNode();
        if (doubleLinkList->GetNode())
        {
            do
            {
                auto* entity = reinterpret_cast<CPhysical*>(node->pItem);
                auto* pPedEntity = static_cast<CPed*>(entity);
                auto* pVehicleEntity = static_cast<CVehicle*>(entity);
                auto* pObjectEntity = static_cast<CObject*>(entity);

                node = node->pNext;

                bool bProcessEntityCollision = true;
                if (entity->m_nType != ENTITY_TYPE_BUILDING
                    && (entity->m_nType != ENTITY_TYPE_OBJECT || !entity->physicalFlags.bDisableCollisionForce))
                {
                    if (m_nType != ENTITY_TYPE_PED || entity->m_nType != ENTITY_TYPE_OBJECT
                        || !entity->IsStatic()
                        || pObjectEntity->objectFlags.bIsExploded)
                    {
                        bProcessEntityCollision = false;
                    }
                }
                if (entity != this
                    && entity->m_nScanCode != CWorld::ms_nCurrentScanCode
                    && entity->m_bUsesCollision && (!m_bHasHitWall || bProcessEntityCollision))
                {
                    if (entity->GetIsTouching(vecBoundCentre, fBoundingSphereRadius))
                    {
                        bool bCollisionDisabled = false;
                        bool bCollidedEntityCollisionIgnored = false;
                        bool bCollidedEntityUnableToMove = false;
                        bool bThisOrCollidedEntityStuck = false;
                        if (entity->m_nType == ENTITY_TYPE_BUILDING)
                        {
                            if (physicalFlags.bDisableCollisionForce
                                && (m_nType != ENTITY_TYPE_VEHICLE || pVehicleEntity->m_vehicleSubType == VEHICLE_TRAIN))
                            {
                                bCollisionDisabled = true;
                            }
                            else
                            {
                                if (m_pAttachedTo)
                                {
                                    uint8 attachedEntityType = m_pAttachedTo->m_nType;
                                    if (attachedEntityType > ENTITY_TYPE_BUILDING && attachedEntityType < ENTITY_TYPE_DUMMY
                                        && m_pAttachedTo->physicalFlags.bDisableCollisionForce)
                                    {
                                        bCollisionDisabled = true;
                                    }
                                }
                                else if (m_pEntityIgnoredCollision == entity)
                                {
                                    bCollisionDisabled = true;
                                }

                                else if (!physicalFlags.bDisableZ || physicalFlags.bApplyGravity)
                                {
                                    if (   physicalFlags.bDontCollideWithFlyers
                                        && m_nStatus // todo:  == STATUS_PLAYER_PLAYBACK_FROM_BUFFER
                                        && m_nStatus != STATUS_HELI
                                        && entity->DoesNotCollideWithFlyers()
                                    ) {
                                        bCollisionDisabled = true;
                                    }
                                }
                                else
                                {
                                    bCollisionDisabled = true;
                                }
                            }
                        }
                        else
                        {
                            SpecialEntityPreCollisionStuff(entity, true, &bCollisionDisabled, &bCollidedEntityCollisionIgnored, 
                                &bCollidedEntityUnableToMove, &bThisOrCollidedEntityStuck);
                        }

                        if (m_nType == ENTITY_TYPE_PED)
                        {
                            physicalFlags.b13 = true;
                        }

                        if (bCollidedEntityCollisionIgnored || bCollisionDisabled)
                            continue;

                        entity->m_nScanCode = CWorld::ms_nCurrentScanCode;
                        int32 totalColPointsToProcess = ProcessEntityCollision(entity, colPoints);
                        if (totalColPointsToProcess <= 0)
                            continue;

                        for (int32 colpointIndex = 0; colpointIndex < totalColPointsToProcess; colpointIndex++) {
                            CColPoint* colPoint = &colPoints[colpointIndex];
                            if (colPoint->m_fDepth > 0.0f) {
                                uint8 pieceTypeB = colPoint->m_nPieceTypeB;
                                if (pieceTypeB < 13 || pieceTypeB > 16) {
                                    totalAcceptableColPoints++;
                                    if (m_nType == ENTITY_TYPE_VEHICLE && entity->m_nType == ENTITY_TYPE_PED && colPoint->m_vecNormal.z < 0.0f) {
                                        vecShift.x += colPoint->m_vecNormal.x;
                                        vecShift.y += colPoint->m_vecNormal.y;
                                        vecShift.z += colPoint->m_vecNormal.z * 0.0f;
                                        fMaxColPointDepth = std::max(fMaxColPointDepth, colPoint->m_fDepth);
                                    } else {
                                        if (m_nType != ENTITY_TYPE_PED || entity->m_nType != ENTITY_TYPE_OBJECT || !entity->physicalFlags.bDisableMoveForce ||
                                            fabs(colPoint->m_vecNormal.z) <= 0.1f) {
                                            vecShift += colPoint->m_vecNormal;
                                            fMaxColPointDepth = std::max(fMaxColPointDepth, colPoint->m_fDepth);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } while (node);
        }
    } while (scanListIndex);

    if (totalAcceptableColPoints == 0) {
        return false;
    }

    float shiftMagnitude = vecShift.Magnitude();
    if (shiftMagnitude > 1.0f) { // normalize the shift boi
        float shiftMultiplier = 1.0f / shiftMagnitude;
        vecShift *= shiftMultiplier;
    }

    CVector& vecEntityPosition = GetPosition();
    if (vecShift.z >= -0.5f) {
        if (m_nType != ENTITY_TYPE_PED) {
            vecEntityPosition += vecShift * fMaxColPointDepth * 1.5f;
        } else {
            float fDepthMultiplied = 1.5f * fMaxColPointDepth;
            if (fDepthMultiplied >= 0.005f) {
                if (fDepthMultiplied > 0.3f) {
                    vecEntityPosition += vecShift * fMaxColPointDepth * 0.3f;
                }
            } else {
                vecEntityPosition += vecShift * fMaxColPointDepth * 0.005f;
            }

            vecEntityPosition += vecShift * fDepthMultiplied;
        }
    } else {
        vecEntityPosition += vecShift * fMaxColPointDepth * 0.75f;
    }

    if (m_nType != ENTITY_TYPE_VEHICLE || 1.5f <= 0.0f) {
        return true;
    }

    if (vecShift.z < 0.0f) {
        vecShift.z = 0.0f;
    }

    m_vecMoveSpeed += vecShift * 0.008f * CTimer::GetTimeStep();
    return true;
}

// Used in driving school mission
// 0x546DB0
void CPhysical::PlacePhysicalRelativeToOtherPhysical(CPhysical* relativeToPhysical, CPhysical* physicalToPlace, CVector offset)
{
    CVector vecRelativePosition = *relativeToPhysical->m_matrix * offset;
    vecRelativePosition += (CTimer::GetTimeStep() * 0.9f) * relativeToPhysical->m_vecMoveSpeed;
    CWorld::Remove(physicalToPlace);
    *(CMatrix*)physicalToPlace->m_matrix = *relativeToPhysical->m_matrix;
    physicalToPlace->GetPosition() = vecRelativePosition;
    physicalToPlace->m_vecMoveSpeed = relativeToPhysical->m_vecMoveSpeed;
    physicalToPlace->UpdateRW();
    physicalToPlace->UpdateRwFrame();
    CWorld::Add(physicalToPlace);
}

// Unused
// 0x546ED0
float CPhysical::ApplyScriptCollision(CVector arg0, float arg1, float arg2, CVector* arg3)
{
    return ((float(__thiscall*)(CPhysical*, CVector, float, float, CVector*))0x546ED0)(this, arg0, arg1, arg2, arg3);
}

void CPhysical::PositionAttachedEntity()
{
    if (!m_pAttachedTo)
        return;

    auto* pAttachedToVehicle = static_cast<CVehicle*>(m_pAttachedTo);
    auto* pAttachedToAutmobile = static_cast<CAutomobile*>(m_pAttachedTo);
    auto* pAttachedToBike = static_cast<CBike*>(m_pAttachedTo);

    CMatrix attachedEntityMatrix;
    CMatrix attachedEntityRotationMatrix;
    CMatrix attachedToEntityMatrix (m_pAttachedTo->GetMatrix());
    if (m_pAttachedTo->IsVehicle() && pAttachedToVehicle->IsBike()) {
        pAttachedToBike->CalculateLeanMatrix();
        attachedToEntityMatrix = pAttachedToBike->m_mLeanMatrix;
    }
    else {
        if (IsObject() && m_pAttachedTo->m_nModelIndex == MODEL_FORKLIFT) {
            RwFrame* carPart = pAttachedToAutmobile->m_aCarNodes[CAR_MISC_A];
            if (carPart)
                attachedToEntityMatrix.UpdateMatrix(RwFrameGetLTM(carPart));
        }
    }

    if (m_qAttachedEntityRotation.imag != 0.0f) {
        RwMatrix rotationMatrix;
        RtQuatConvertToMatrix((RtQuat*)&m_qAttachedEntityRotation, &rotationMatrix);
        attachedEntityMatrix.UpdateMatrix(&rotationMatrix);
        attachedEntityMatrix = attachedToEntityMatrix * attachedEntityMatrix;
        CVector vecTranslation = attachedToEntityMatrix * m_vecAttachOffset;
        attachedEntityMatrix.SetTranslateOnly(vecTranslation);
    }
    else {
        if (physicalFlags.bInfiniteMass) {
            attachedEntityMatrix = *m_matrix;
        }
        else {
            attachedEntityRotationMatrix.ResetOrientation();
            attachedEntityRotationMatrix.Rotate(m_vecAttachedEntityRotation);
            attachedEntityMatrix = attachedToEntityMatrix;
            attachedEntityMatrix *= attachedEntityRotationMatrix;
        }
        attachedEntityMatrix.GetPosition() += Multiply3x3(attachedToEntityMatrix, m_vecAttachOffset);
    }
    SetMatrix(attachedEntityMatrix);

    if (IsObject()) {
        if (IsStatic())
            SetIsStatic(false);
        physicalFlags.bAttachedToEntity = true;
        m_nFakePhysics = 0;
    }

    bool bUpdateSpeed = false;
    if (!m_pAttachedTo->IsVehicle() || !this->IsObject() && !this->IsVehicle()) {
        if (m_nModelIndex == MODEL_SATCHEL && m_pAttachedTo->IsObject() && !m_pAttachedTo->m_bUsesCollision) {
            DettachAutoAttachedEntity();
            m_bUsesCollision = true;
            return;
        }
        bUpdateSpeed = true;
    }

    bool bDettachEntity = false;
    if (!bUpdateSpeed)
    {
        if (m_pAttachedTo->m_nModelIndex == MODEL_DUMPER) {
            int16 wMiscComponentAngle = pAttachedToAutmobile->m_wMiscComponentAngle;
            if (wMiscComponentAngle && wMiscComponentAngle != pAttachedToAutmobile->m_wMiscComponentAnglePrev) {
                bDettachEntity = true;
            }
            else if (m_fDamageIntensity > 0.0f) {
                if (m_pDamageEntity) {
                    if (m_pDamageEntity->m_nType  == ENTITY_TYPE_BUILDING)
                        bDettachEntity = true;
                }
            }
        }
        else {
            if (m_pAttachedTo->m_nModelIndex != MODEL_FORKLIFT) {
                if (this->IsVehicle()) {
                    CMatrix attachedToEntityMatrix = m_pAttachedTo->GetMatrix();
                    if (fabs(attachedToEntityMatrix.GetRight().z) > 0.707f || fabs(attachedToEntityMatrix.GetForward().z) > 0.707f) { // 0.707 == sin(DegreesToRadians(45))
                        DettachEntityFromEntity(0.0f, 0.0f, 1.0f, false);
                        return;
                    }
                }
                bUpdateSpeed = true;
            }
            else if (!pAttachedToAutmobile->m_wMiscComponentAngle && pAttachedToAutmobile->m_wMiscComponentAnglePrev
                || m_fDamageIntensity > 0.1f * m_fMass && m_pDamageEntity && m_pDamageEntity->m_nType  == ENTITY_TYPE_BUILDING) {
                bDettachEntity = true;
            }
        }
        if (!bUpdateSpeed && !bDettachEntity) {
            float fDamagedIntensity = m_pAttachedTo->m_fDamageIntensity;
            CMatrix* pMatrix = m_pAttachedTo->m_matrix;
            if ((fDamagedIntensity <= 0.0f || m_pAttachedTo->GetUp().z >= 0.1f) && (fDamagedIntensity <= 1.0f || m_pAttachedTo->GetForward().z <= 0.87f)) {
                float fDotProduct = DotProduct(&m_pAttachedTo->m_vecLastCollisionImpactVelocity, &pMatrix->GetUp());
                if ((fDamagedIntensity <= 500.0f || fDotProduct >= 0.7f || 0.3f * 0.3f <= m_pAttachedTo->m_vecMoveSpeed.SquaredMagnitude())) {
                    bUpdateSpeed = true;
                }
            }
        }
    }

    if (!bUpdateSpeed) {
        auto* pAttachedTo = m_pAttachedTo;
        DettachAutoAttachedEntity();
        if (!physicalFlags.bDisableCollisionForce) {
            float randomNumber = CGeneral::GetRandomNumberInRange(-1.0f, 1.0f);
            CMatrix& attachedToEntityMatrix = pAttachedTo->GetMatrix();
            CVector randomRight = attachedToEntityMatrix.GetRight() * randomNumber;
            CVector randomForward = attachedToEntityMatrix.GetForward() * randomNumber;
            CVector force = (randomRight + randomForward) * (m_fMass * 0.02f);
            ApplyMoveForce(force);
            if (pAttachedToAutmobile->m_wMiscComponentAngle > pAttachedToAutmobile->m_wMiscComponentAnglePrev)
                ApplyMoveForce(pAttachedTo->GetMatrix().GetUp() * m_fMass * 0.02f);
        }
        return;
    }

    if (physicalFlags.bInfiniteMass) {
        CVector vecMoveSpeed = GetPosition() - m_vecAttachedEntityRotation;
        float fSquaredMagnitude = vecMoveSpeed.SquaredMagnitude();
        m_vecAttachedEntityRotation = GetPosition();
        if (fSquaredMagnitude > 4.0f)
            vecMoveSpeed *= 2.0f / sqrt(fSquaredMagnitude);

        float fTimeStep = 1.0f;
        if (CTimer::GetTimeStep() >= 1.0f)
            fTimeStep = CTimer::GetTimeStep();

        vecMoveSpeed *= 1.0f / fTimeStep;
        CVector vecMoveSpeedDifference = vecMoveSpeed - m_vecMoveSpeed;
        m_vecMoveSpeed = vecMoveSpeed;
        CVector vecForce = vecMoveSpeedDifference * m_fMass * -1.0f;
        CVector vecCenterOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
        ApplyForce(vecForce, vecCenterOfMassMultiplied, true);
        if (m_pAttachedTo->IsVehicle() || m_pAttachedTo->IsObject()) {
            if (m_pAttachedTo->m_bUsesCollision && !m_pAttachedTo->physicalFlags.bDisableCollisionForce) {
                CVector vecDistance = (vecCenterOfMassMultiplied + GetPosition()) - m_pAttachedTo->GetPosition();
                m_pAttachedTo->ApplyForce(vecForce * -1.0f, vecDistance, true);
            }
            float fRotationInRadians = m_pAttachedTo->GetHeading() - GetHeading();
            if (fRotationInRadians > PI) 
                fRotationInRadians -= PI * 2;
            else if (fRotationInRadians < -PI)
                fRotationInRadians += PI * 2;
            fRotationInRadians = clamp<float>(fRotationInRadians, -0.5f, 0.5f);
            m_vecTurnSpeed.z += fRotationInRadians * 0.00001f * m_fMass;
        }
    }
    else {
        if (m_pAttachedTo->IsVehicle() || m_pAttachedTo->IsObject()) {
            m_vecMoveSpeed = m_pAttachedTo->GetSpeed(GetPosition() - m_pAttachedTo->GetPosition());
            m_vecTurnSpeed = m_pAttachedTo->m_vecTurnSpeed;
        }
    }
}

// 0x547B80
void CPhysical::ApplySpeed()
{
    auto* object = static_cast<CObject*>(this);
    float fOldTimeStep = CTimer::GetTimeStep();
    if (physicalFlags.bDisableZ) {
        if (physicalFlags.bApplyGravity) {
            if (fOldTimeStep * m_vecMoveSpeed.z + GetPosition().z < CWorld::SnookerTableMin.z) {
                GetPosition().z = CWorld::SnookerTableMin.z;
                ResetMoveSpeed();
                ResetTurnSpeed();
            }
            ApplyMoveSpeed();
            ApplyTurnSpeed();
            CTimer::UpdateTimeStep(fOldTimeStep);
            return;
        }

        float fTimeStepX = 1000.0f;
        float fTimeStepY = 1000.0f;
        float fNewPositionX = fOldTimeStep * m_vecMoveSpeed.x + GetPosition().x;
        if (fNewPositionX <= CWorld::SnookerTableMax.x || m_vecMoveSpeed.x <= 0.0f)
        {
            if (fNewPositionX >= CWorld::SnookerTableMin.x || m_vecMoveSpeed.x >= 0.0f) {
                // nothing
            }
            else{
             fTimeStepX = (CWorld::SnookerTableMin.x - GetPosition().x) / m_vecMoveSpeed.x;
            }
        }
        else {
            fTimeStepX = (CWorld::SnookerTableMax.x - GetPosition().x) / m_vecMoveSpeed.x;
        }
        
        float fNewPositionY = CTimer::GetTimeStep() * m_vecMoveSpeed.y + GetPosition().y;
        if (fNewPositionY <= CWorld::SnookerTableMax.y || m_vecMoveSpeed.y <= 0.0f) {
            if (fNewPositionY >= CWorld::SnookerTableMin.y || m_vecMoveSpeed.y >= 0.0f) {
                // nothing
            }
            else {
                fTimeStepY = (CWorld::SnookerTableMin.y - GetPosition().y) / m_vecMoveSpeed.y;
            }
        }
        else {
            fTimeStepY = (CWorld::SnookerTableMax.y - GetPosition().y) / m_vecMoveSpeed.y;
        }

        bool bTableWidthIsLessThanHeight = true;
        if (CWorld::SnookerTableMax.x - CWorld::SnookerTableMin.x < CWorld::SnookerTableMax.y - CWorld::SnookerTableMin.y)
            bTableWidthIsLessThanHeight = false;
        bool bApplyFriction = false;
        float fNormalX = 0.0f;
        float fNormalY = 0.0f;
        float fAbsoluteMoveSpeed = 0.0f;
        float fNewTimeStep = 0.0f;
        if (fTimeStepX < fTimeStepY && fTimeStepX < 1000.0f) {
            fNormalX = -1.0f;
            fAbsoluteMoveSpeed = fabs(m_vecMoveSpeed.x);
            if (m_vecMoveSpeed.x <= 0.0)
                fNormalX = 1.0f;
            CTimer::UpdateTimeStep(fTimeStepX);
            ApplyMoveSpeed();
            ApplyTurnSpeed();
            float fTableY = (CWorld::SnookerTableMin.y + CWorld::SnookerTableMax.y) * 0.5f;
            if (CWorld::SnookerTableMax.y - 0.06f >= GetPosition().y
                && CWorld::SnookerTableMin.y + 0.06f <= GetPosition().y
                && (bTableWidthIsLessThanHeight || fTableY - 0.06f >= GetPosition().y || GetPosition().y >= fTableY + 0.06f)) {
                m_vecMoveSpeed.x = m_vecMoveSpeed.x * -1.0f;
                fNewTimeStep = fOldTimeStep - fTimeStepX;
            }
            else
            {
                physicalFlags.bApplyGravity = true;
                float fTimeStepMoveSpeedX = fOldTimeStep * m_vecMoveSpeed.x;
                if (fTimeStepMoveSpeedX <= 0.03f) {
                    if (fTimeStepMoveSpeedX < -0.03f)
                        m_vecMoveSpeed.x = -(0.03f / fOldTimeStep);
                    fNewTimeStep = fOldTimeStep - fTimeStepX;
                }
                else {
                    m_vecMoveSpeed.x = 0.03f / fOldTimeStep;
                    fNewTimeStep = fOldTimeStep - fTimeStepX;
                }
            }
            bApplyFriction = true;
        }
        if (!bApplyFriction && fTimeStepY < 1000.0f) {
            fNormalY = -1.0f;
            fAbsoluteMoveSpeed = fabs(m_vecMoveSpeed.y);
            if (m_vecMoveSpeed.y <= 0.0f)
                fNormalY = 1.0f;
            CTimer::UpdateTimeStep(fTimeStepY);
            ApplyMoveSpeed();
            ApplyTurnSpeed();
            float fTableX = (CWorld::SnookerTableMin.x + CWorld::SnookerTableMax.x) * 0.5f;
            if (CWorld::SnookerTableMax.x - 0.06f < GetPosition().x
                || CWorld::SnookerTableMin.x + 0.06f > GetPosition().x
                || bTableWidthIsLessThanHeight &&  fTableX - 0.06f < GetPosition().x && GetPosition().x < fTableX + 0.06f) {
                physicalFlags.bApplyGravity = true;
                float fTimeStepMoveSpeedY = fOldTimeStep * m_vecMoveSpeed.y;
                if (fTimeStepMoveSpeedY <= 0.03f) {
                    if (fTimeStepMoveSpeedY < -0.03f) {
                        m_vecMoveSpeed.y = -(0.03f / fOldTimeStep);
                    }
                }
                else
                {
                    m_vecMoveSpeed.y = 0.03f / fOldTimeStep;
                }
            }
            else {
                m_vecMoveSpeed.y = m_vecMoveSpeed.y * -1.0f;
            }
            fNewTimeStep = fOldTimeStep - fTimeStepY;
            bApplyFriction = true;
        }

        if (bApplyFriction) {
            CTimer::UpdateTimeStep(fNewTimeStep);
            if (fAbsoluteMoveSpeed > 0.0f) {
                float fRadius = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundRadius();
                CVector thePosition = CVector(fNormalX * fRadius, fNormalY * fRadius, 0.0f);
                CColPoint colPoint;
                colPoint.m_vecPoint = GetPosition() - thePosition;
                colPoint.m_vecNormal = CVector(fNormalX, fNormalY, 0.0f);
                ApplyFriction(10.0f * fAbsoluteMoveSpeed, colPoint);
                if (m_nType == ENTITY_TYPE_OBJECT)
                {
                    AudioEngine.ReportMissionAudioEvent(AE_CAS4_FE, object);
                    object->m_nLastWeaponDamage = 4 * (object->m_nLastWeaponDamage == 0xFF) + WEAPON_RUNOVERBYCAR;
                }
            }
        }
        ApplyMoveSpeed();
        ApplyTurnSpeed();
        CTimer::UpdateTimeStep(fOldTimeStep);
        return;
    }

    if (!physicalFlags.bDisableMoveForce || m_nType != ENTITY_TYPE_OBJECT || object->m_fDoorStartAngle <= -1000.0f) {
        ApplyMoveSpeed();
        ApplyTurnSpeed();
        CTimer::UpdateTimeStep(fOldTimeStep);
        return;
    }

    float fDoorStartAngle = object->m_fDoorStartAngle;
    float fHeading = GetHeading();
    if (fDoorStartAngle + PI >= fHeading) {
        if (fDoorStartAngle - PI > fHeading)
            fHeading += PI * 2;
    }
    else {
        fHeading -= PI * 2;
    }

    float fNewTimeStep = -1000.0f;
    float fTheDoorAngle  = DegreesToRadians(108.0f) + fDoorStartAngle;
    float fHeadingTimeStep = CTimer::GetTimeStep() * m_vecTurnSpeed.z + fHeading;
    if (m_vecTurnSpeed.z <= 0.0f || fHeadingTimeStep <= DegreesToRadians(108.0f) + fDoorStartAngle) {
        if (m_vecTurnSpeed.z < 0.0f) {
            float fTheDoorAngle = fDoorStartAngle - DegreesToRadians(108.0f);
            if (fHeadingTimeStep < fTheDoorAngle)
                fNewTimeStep = (fTheDoorAngle - fHeading) / m_vecTurnSpeed.z;
        }
    }
    else
    {
        fNewTimeStep = (fTheDoorAngle - fHeading) / m_vecTurnSpeed.z;
    }
    if (-CTimer::GetTimeStep() <= fNewTimeStep) {
        CTimer::UpdateTimeStep(fNewTimeStep);
        ApplyTurnSpeed();
        m_vecTurnSpeed.z = -0.2f * m_vecTurnSpeed.z;
        CTimer::UpdateTimeStep(fOldTimeStep - fNewTimeStep);
        physicalFlags.b31 = true;
    }
    ApplyMoveSpeed();
    ApplyTurnSpeed();
    CTimer::UpdateTimeStep(fOldTimeStep);
    if (object->objectFlags.bIsDoorMoving) {
        float fNewHeading = GetHeading();
        if (fNewHeading + PI >= fDoorStartAngle) {
            if (fNewHeading - PI > fDoorStartAngle)
                fNewHeading -= PI * 2;
        }
        else {
            fNewHeading += PI * 2;
        }

        fHeading -= fDoorStartAngle;
        fNewHeading -= fDoorStartAngle;
        if (fabs(fHeading) < 0.001f)
            fHeading = 0.0f;
        if (fabs(fNewHeading) < 0.001f)
            fNewHeading = 0.0f;
        if (fHeading * fNewHeading < 0.0f)
            m_vecTurnSpeed.z = 0.0f;
    }
}

// 0x548320
void CPhysical::UnsetIsInSafePosition()
{
    m_vecMoveSpeed *= -1.0f;
    m_vecTurnSpeed *= -1.0f;
    ApplySpeed();
    m_vecMoveSpeed *= -1.0f;
    m_vecTurnSpeed *= -1.0f;
    m_bIsInSafePosition = false;
}

// 0x5483D0
void CPhysical::ApplyFriction()
{
    if (physicalFlags.bDisableZ)
    {
        const CVector& vecPosition = GetPosition();
        float fSphereRadius = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundRadius();
        CColPoint colPoint;
        colPoint.m_vecPoint.x = vecPosition.x - (0.0f * fSphereRadius);
        colPoint.m_vecPoint.y = vecPosition.y - (0.0f * fSphereRadius);
        colPoint.m_vecPoint.z = vecPosition.z - fSphereRadius;
        colPoint.m_vecNormal = CVector (0.0f, 0.0f, 1.0f);

        ApplyFriction(CTimer::GetTimeStep() * 0.001f, colPoint);
        m_vecTurnSpeed.z = pow(0.98f, CTimer::GetTimeStep()) * m_vecTurnSpeed.z;
    }

    m_vecMoveSpeed += m_vecFrictionMoveSpeed;
    m_vecTurnSpeed += m_vecFrictionTurnSpeed;
    ResetFrictionMoveSpeed();
    ResetFrictionTurnSpeed();

    auto* vehicle = static_cast<CVehicle*>(this);
    if (m_nType == ENTITY_TYPE_VEHICLE && vehicle->m_vehicleType == VEHICLE_BIKE
        && !physicalFlags.b32 && m_nStatus == STATUS_ABANDONED 
        && fabs(GetUp().z) < 0.707f
        && 0.05f * 0.05f > m_vecMoveSpeed.SquaredMagnitude() && 0.01f * 0.01f > m_vecTurnSpeed.SquaredMagnitude())
    {                                    
        m_vecMoveSpeed *= pow(0.5f, CTimer::GetTimeStep());
    }
}

// 0x548680
bool CPhysical::ApplyCollision(CEntity* theEntity, CColPoint& colPoint, float& thisDamageIntensity, float& entityDamageIntensity)
{
    auto* entity = static_cast<CPhysical*>(theEntity);
    auto* entityObject = static_cast<CObject*>(entity);
    auto* entityPed = static_cast<CPed*>(entity);
    auto* entityVehicle = static_cast<CVehicle*>(entity);

    auto* thisObject = static_cast<CObject*>(this);
    auto* thisPed = static_cast<CPed*>(this);
    auto* thisVehicle = static_cast<CVehicle*>(this);

    bool bThisPedIsStandingOnEntity = false;
    bool bEntityPedIsStandingOnThis = false;
    bool bEntityCollisionForceDisabled = false;

    float fThisMassFactor = 0.0f;
    float fEntityMassFactor = 1.0f;

    if (!entity->physicalFlags.bDisableTurnForce || physicalFlags.bDisableMoveForce)
    {
        fThisMassFactor = 2.0f;
        if (!physicalFlags.bMakeMassTwiceAsBig)
        {
            fThisMassFactor = 1.0f;
        }
    }
    else
    {
        fThisMassFactor = 10.0f;
        if (entity->m_nType == ENTITY_TYPE_PED && entityPed->m_standingOnEntity == this)
        {
            bEntityPedIsStandingOnThis = true;
        }
    }

    if (physicalFlags.bDisableTurnForce)
    {
        if (m_nType == ENTITY_TYPE_PED && thisPed->IsPlayer()
            && entity->m_nType == ENTITY_TYPE_VEHICLE
            && (entity->m_nStatus == STATUS_ABANDONED || entity->m_nStatus == STATUS_WRECKED || m_bIsStuck))
        {
            float fTheEntityMass = entity->m_fMass - 2000.0f;
            if (fTheEntityMass < 0.0f)
            {
                fTheEntityMass = 0.0f;
            }
            fEntityMassFactor = 1.0f / (fTheEntityMass * 0.0002f + 1.0f);
        }
        else if (!entity->physicalFlags.bDisableMoveForce)
        {
            fEntityMassFactor = 10.0f;
        }
        if (m_nType == ENTITY_TYPE_PED && thisPed->m_standingOnEntity == entity)
        {
            bThisPedIsStandingOnEntity = true;
            fEntityMassFactor = 10.0f;
        }
    }
    else if (m_nType == ENTITY_TYPE_VEHICLE && thisVehicle->m_pTrailer)
    {
        fEntityMassFactor = (thisVehicle->m_pTrailer->m_fMass + m_fMass) / m_fMass;
    }
    else
    {
        fEntityMassFactor = 2.0f;
        if (!entity->physicalFlags.bMakeMassTwiceAsBig)
        {
            fEntityMassFactor = 1.0f;
        }
    }

    if (entity->physicalFlags.bDisableCollisionForce && !entity->physicalFlags.bCollidable
        || entity->m_pAttachedTo && !entity->physicalFlags.bInfiniteMass)
    {
        bEntityCollisionForceDisabled = true;
        bThisPedIsStandingOnEntity = false;
    }

    CVector vecThisCentreOfMassMultiplied;
    CVector vecEntityCentreOfMassMultiplied;

    vecThisCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
    vecEntityCentreOfMassMultiplied = Multiply3x3(entity->GetMatrix(), entity->m_vecCentreOfMass);

    if (physicalFlags.bInfiniteMass)
    {
        vecThisCentreOfMassMultiplied = CVector(0.0f, 0.0f, 0.0f);
    }

    if (entity->physicalFlags.bInfiniteMass)
    {
        vecEntityCentreOfMassMultiplied = CVector(0.0f, 0.0f, 0.0f);
    }

    if (m_nType == ENTITY_TYPE_VEHICLE && entity->m_nType == ENTITY_TYPE_OBJECT
        && entityObject->objectFlags.bIsLampPost
        || entity->m_nType == ENTITY_TYPE_VEHICLE && m_nType == ENTITY_TYPE_OBJECT &&
        thisObject->objectFlags.bIsLampPost)
    {
        colPoint.m_vecNormal.z = 0.0f;
    }

    if (entity->IsStatic() && !bEntityCollisionForceDisabled)
    {
        if (physicalFlags.bDisableTurnForce)
        {
            float fThisSpeedDotProduct = DotProduct(m_vecMoveSpeed, colPoint.m_vecNormal);
            if (fThisSpeedDotProduct < 0.0f)
            {
                if (entity->m_nType != ENTITY_TYPE_OBJECT)
                {
                    if (entity->physicalFlags.bDisableCollisionForce)
                    {
                        return ApplyCollision(entity, colPoint, thisDamageIntensity);
                    }

                    entity->SetIsStatic(false);
                }
                else
                {
                    thisDamageIntensity = -(fThisSpeedDotProduct * m_fMass);
                    entityDamageIntensity = thisDamageIntensity;

                    if (entity->physicalFlags.bDisableCollisionForce)
                    {
                        return ApplyCollision(entity, colPoint, thisDamageIntensity);
                    }

                    CObjectData* pEntityObjectInfo = entityObject->m_pObjectInfo;
                    if (pEntityObjectInfo->m_fUprootLimit >= 9999.0f || thisDamageIntensity <= pEntityObjectInfo->m_fUprootLimit)
                    {
                        return ApplyCollision(entity, colPoint, thisDamageIntensity);
                    }

                    if (IsGlassModel(entity))
                    {
                        CGlass::WindowRespondsToCollision(entity, thisDamageIntensity, m_vecMoveSpeed, colPoint.m_vecPoint, false);
                    }
                    else
                    {
                        if (!entity->physicalFlags.bDisableCollisionForce)
                        {
                            entity->SetIsStatic(false);
                            CWorld::Players[CWorld::PlayerInFocus].m_nHavocCaused += 2;
                            CStats::IncrementStat(STAT_COST_OF_PROPERTY_DAMAGED, static_cast<float>(rand() % 30 + 30));
                        }
                    }
                }
            }
        }
        else
        {
            CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
            CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

            if (physicalFlags.bAddMovingCollisionSpeed && m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeA == SURFACE_CAR_MOVINGCOMPONENT)
                vecThisSpeed += thisVehicle->AddMovingCollisionSpeed(vecDistanceToPointFromThis);

            float fThisSpeedDotProduct = DotProduct(vecThisSpeed, colPoint.m_vecNormal);
            if (fThisSpeedDotProduct < 0.0f)
            {
                if (entity->m_nType != ENTITY_TYPE_OBJECT)
                {
                    if (entity->physicalFlags.bDisableCollisionForce)
                    {
                        return ApplyCollision(entity, colPoint, thisDamageIntensity);
                    }

                    entity->SetIsStatic(false);
                    CWorld::Players[CWorld::PlayerInFocus].m_nHavocCaused += 2;
                    CStats::IncrementStat(STAT_COST_OF_PROPERTY_DAMAGED, static_cast<float>(rand() % 30 + 30));
                }
                else
                {
                    CVector vecThisDifference = (vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied);
                    CVector vecThisCrossProduct;
                    vecThisCrossProduct.Cross(vecThisDifference, colPoint.m_vecNormal);
                    float squaredMagnitude = vecThisCrossProduct.SquaredMagnitude();
                    float fThisCollisionMass = 1.0f / (squaredMagnitude / m_fTurnMass + 1.0f / m_fMass);
                    if (!m_bHasHitWall)
                    {
                        thisDamageIntensity = -((m_fElasticity + 1.0f) * fThisCollisionMass * fThisSpeedDotProduct);
                    }
                    else
                    {
                        thisDamageIntensity = fThisCollisionMass * fThisSpeedDotProduct * -1.0f;
                    }

                    entityDamageIntensity = thisDamageIntensity;

                    CObjectData* pEntityObjectInfo = entityObject->m_pObjectInfo;

                    float fObjectDamageMultiplier = 1.0f;
                    if (m_nType == ENTITY_TYPE_VEHICLE && thisVehicle->m_vehicleSubType == VEHICLE_BIKE)
                    {
                        fObjectDamageMultiplier = 3.0f;
                    }

                    if (entityObject->m_nColDamageEffect)
                    {
                        float fObjectDamage = fObjectDamageMultiplier * thisDamageIntensity;
                        if (fObjectDamage > 20.0f)
                        {
                            entityObject->ObjectDamage(fObjectDamage, &colPoint.m_vecPoint, &colPoint.m_vecNormal, this, WEAPON_UNIDENTIFIED);
                            if (!entity->m_bUsesCollision)
                            {
                                if (!physicalFlags.bDisableCollisionForce)
                                {
                                    float fColDamageMultiplier = pEntityObjectInfo->m_fColDamageMultiplier;
                                    float fCollisionDamage = fColDamageMultiplier + fColDamageMultiplier;
                                    CVector vecMoveForce = (colPoint.m_vecNormal * thisDamageIntensity) / fCollisionDamage;
                                    ApplyForce(vecMoveForce, vecDistanceToPointFromThis, true);
                                }

                                float fDamageIntensityMultiplier = pEntityObjectInfo->m_fColDamageMultiplier / fThisCollisionMass;
                                float fCollisionImpact1 = fDamageIntensityMultiplier * thisDamageIntensity + fDamageIntensityMultiplier * thisDamageIntensity;

                                AudioEngine.ReportCollision(
                                    this,
                                    entity,
                                    colPoint.m_nSurfaceTypeA,
                                    colPoint.m_nSurfaceTypeB,
                                    colPoint.m_vecPoint,
                                    &colPoint.m_vecNormal,
                                    fCollisionImpact1,
                                    1.0f,
                                    false,
                                    false
                                );
                                return false;
                            }
                        }
                    }
                    if (entity->physicalFlags.bDisableCollisionForce || pEntityObjectInfo->m_fUprootLimit >= 9999.0f
                        || thisDamageIntensity <= pEntityObjectInfo->m_fUprootLimit && (!m_bIsStuck || !m_bHasHitWall))
                    {
                        if (IsGlassModel(entity))
                        {
                            CGlass::WindowRespondsToSoftCollision(entityObject, thisDamageIntensity);
                        }
                        return ApplyCollision(entity, colPoint, thisDamageIntensity);
                    }

                    if (IsGlassModel(entity))
                    {
                        CGlass::WindowRespondsToCollision(entity, thisDamageIntensity, m_vecMoveSpeed, colPoint.m_vecPoint, false);
                    }
                    else
                    {
                        entity->SetIsStatic(false);
                    }

                    int32 entityModelIndex = entity->m_nModelIndex;
                    if (entityModelIndex != ModelIndices::MI_FIRE_HYDRANT || entityObject->objectFlags.bIsExploded)
                    {
                        if (entityModelIndex != ModelIndices::MI_PARKINGMETER && entityModelIndex != ModelIndices::MI_PARKINGMETER2 || entityObject->objectFlags.bIsExploded) {
                            if (entity->m_nType != ENTITY_TYPE_OBJECT || pEntityObjectInfo->m_bCausesExplosion) {
                                // nothing
                            } else {
                                entityObject->objectFlags.bIsExploded = true;
                            }
                        } else {
                            CPickups::CreateSomeMoney(entity->GetPosition(), rand() % 100);
                            entityObject->objectFlags.bIsExploded = true;
                        }
                    }
                    else
                    {
                        g_fx.TriggerWaterHydrant(entity->GetPosition());
                        entityObject->objectFlags.bIsExploded = true;
                    }

                    if (!physicalFlags.bDisableCollisionForce && pEntityObjectInfo->m_fUprootLimit > 200.0f)
                    {
                        CVector vecMoveForce = (colPoint.m_vecNormal * 0.2f) * thisDamageIntensity;
                        ApplyForce(vecMoveForce, vecDistanceToPointFromThis, true);
                    }
                }
            }
        }

        if (entity->IsStatic())
        {
            return false;
        }
        if (!entity->physicalFlags.bDisableCollisionForce)
        {
            entity->AddToMovingList();
        }
    }

    if (physicalFlags.bDisableTurnForce)
    {
        if (entity->physicalFlags.bDisableTurnForce)
        {
            bool bApplyEntityCollisionForce = true;
            float fThisMass = m_fMass;
            float fEntityMass = entity->m_fMass;
            float fThisSpeedDotProduct = DotProduct(m_vecMoveSpeed, colPoint.m_vecNormal);
            float fEntitySpeedDotProduct = DotProduct(entity->m_vecMoveSpeed, colPoint.m_vecNormal);
            float fMoveSpeed = 0.0f;
            if (physicalFlags.bDisableCollisionForce || physicalFlags.bDontApplySpeed)
            {
                fMoveSpeed = fThisSpeedDotProduct;
            }
            else
            {
                if (entity->physicalFlags.bDisableCollisionForce || entity->physicalFlags.bDontApplySpeed)
                {
                    fMoveSpeed = fEntitySpeedDotProduct;
                    bApplyEntityCollisionForce = false;
                }
                else
                {
                    if (!thisPed->bPedThirdFlags32) // Hmm?? Is this a bug?
                    {
                        if (fEntitySpeedDotProduct >= 0.0f) {
                            fMoveSpeed = 0.0f;
                        } else {
                            fMoveSpeed = fEntitySpeedDotProduct;
                        }

                        bApplyEntityCollisionForce = false;
                    } else {
                        fMoveSpeed = (fThisMass * fThisSpeedDotProduct * 4.0f + fEntityMass * fEntitySpeedDotProduct) / (fThisMass * 4.0f + fEntityMass);
                    }
                }
            }

            float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
            if (fThisMoveSpeedDifference >= 0.0f) {
                return false;
            }

            float fThisMoveSpeedElasticity = 0.0f;
            float fTheElasticity = (entity->m_fElasticity + m_fElasticity) * 0.5f;
            if (m_bHasHitWall) {
                fThisMoveSpeedElasticity = fMoveSpeed;
            } else {
                fThisMoveSpeedElasticity = fMoveSpeed - fTheElasticity * fThisMoveSpeedDifference;
            }

            thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisMass;

            CVector vecThisMoveForce = colPoint.m_vecNormal * thisDamageIntensity;
            if (!physicalFlags.bDisableCollisionForce && !physicalFlags.bDontApplySpeed)
            {
                ApplyMoveForce(vecThisMoveForce);

                float fCollisionImpact1 = thisDamageIntensity / fThisMass;
                AudioEngine.ReportCollision(this, entity, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
            }

            if (bApplyEntityCollisionForce)
            {
                float fEntityMoveSpeedElasticity = 0.0f;
                if (entity->m_bHasHitWall) {
                    fEntityMoveSpeedElasticity = fMoveSpeed;
                } else {
                    fEntityMoveSpeedElasticity = fMoveSpeed - (fEntitySpeedDotProduct - fMoveSpeed) * fTheElasticity;
                }

                entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityMass);


                CVector vecEntityMoveForce = colPoint.m_vecNormal * entityDamageIntensity * -1.0f;
                if (!entity->physicalFlags.bDisableCollisionForce && !entity->physicalFlags.bDontApplySpeed)
                {
                    if (entity->m_bIsInSafePosition)
                    {
                        entity->UnsetIsInSafePosition();
                    }

                    entity->ApplyMoveForce(vecEntityMoveForce);

                    float fCollisionImpact1 = entityDamageIntensity / fEntityMass;
                    AudioEngine.ReportCollision(
                        entity,
                        this,
                        colPoint.m_nSurfaceTypeB,
                        colPoint.m_nSurfaceTypeA,
                        colPoint.m_vecPoint,
                        &colPoint.m_vecNormal,
                        fCollisionImpact1,
                        1.0f,
                        false,
                        false
                    );
                }
            }
            return true;
        }
    }

    if (physicalFlags.bDisableTurnForce)
    {
        CVector vecDistanceToPoint = colPoint.m_vecPoint - entity->GetPosition();
        CVector vecEntitySpeed = entity->GetSpeed(vecDistanceToPoint);

        if (!entity->physicalFlags.bAddMovingCollisionSpeed || entity->m_nType != ENTITY_TYPE_VEHICLE || colPoint.m_nSurfaceTypeB != SURFACE_CAR_MOVINGCOMPONENT) {
            // nothing
        } else {
            vecEntitySpeed += entityVehicle->AddMovingCollisionSpeed(vecDistanceToPoint);
        }

        float fThisSpeedDotProduct = DotProduct(m_vecMoveSpeed, colPoint.m_vecNormal);
        float fEntitySpeedDotProduct = DotProduct(vecEntitySpeed, colPoint.m_vecNormal);

        float fThisMass = fThisMassFactor * m_fMass;

        CVector vecEntityDifference = (vecDistanceToPoint - vecEntityCentreOfMassMultiplied);
        CVector vecEntityCrossProduct;
        vecEntityCrossProduct.Cross(vecEntityDifference, colPoint.m_vecNormal);
        float squaredMagnitude = vecEntityCrossProduct.SquaredMagnitude();
        float fEntityCollisionMass = 0.0f;
        if (entity->physicalFlags.bDisableMoveForce) {
            fEntityCollisionMass = squaredMagnitude / (fEntityMassFactor * entity->m_fTurnMass);
        } else {
            fEntityCollisionMass = squaredMagnitude / (fEntityMassFactor * entity->m_fTurnMass) + 1.0f / (fEntityMassFactor * entity->m_fMass);
        }

        fEntityCollisionMass = 1.0f / fEntityCollisionMass;

        float fMoveSpeed = 0.0f;
        if (bEntityCollisionForceDisabled) {
            fMoveSpeed = fEntitySpeedDotProduct;
        } else {
            fMoveSpeed = (fEntityCollisionMass * fEntitySpeedDotProduct + fThisMass * fThisSpeedDotProduct) / (fEntityCollisionMass + fThisMass);
        }

        float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
        if (fThisMoveSpeedDifference < 0.0f)
        {
            float fThisMoveSpeedElasticity = 0.0f;
            float fEntityMoveSpeedElasticity = 0.0f;

            float fTheElasticity = (entity->m_fElasticity + m_fElasticity) * 0.5f;
            if (m_bHasHitWall) {
                fThisMoveSpeedElasticity = fMoveSpeed;
            } else {
                fThisMoveSpeedElasticity = fMoveSpeed - fTheElasticity * fThisMoveSpeedDifference;
            }

            if (entity->m_bHasHitWall) {
                fEntityMoveSpeedElasticity = fMoveSpeed;
            } else {
                fEntityMoveSpeedElasticity = fMoveSpeed - (fEntitySpeedDotProduct - fMoveSpeed) * fTheElasticity;
            }

            thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisMass;
            entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityCollisionMass);

            CVector vecThisMoveForce = (thisDamageIntensity / fThisMassFactor) * colPoint.m_vecNormal;
            CVector vecEntityMoveForce = (colPoint.m_vecNormal * (entityDamageIntensity / fEntityMassFactor) * -1.0f);

            if (!physicalFlags.bDisableCollisionForce)
            {
                if (vecThisMoveForce.z < 0.0f)
                {
                    vecThisMoveForce.z = 0.0f;
                }
                if (bThisPedIsStandingOnEntity)
                {
                    vecThisMoveForce.x += vecThisMoveForce.x;
                    vecThisMoveForce.y += vecThisMoveForce.y;
                }

                ApplyMoveForce(vecThisMoveForce);
            }
            if (!entity->physicalFlags.bDisableCollisionForce && !bThisPedIsStandingOnEntity)
            {
                if (entity->m_bIsInSafePosition)
                {
                    entity->UnsetIsInSafePosition();
                }
                entity->ApplyForce(vecEntityMoveForce, vecDistanceToPoint, true);
            }

            float fCollisionImpact1 = thisDamageIntensity / fThisMass;
            AudioEngine.ReportCollision(this, entity, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);

            fCollisionImpact1 = entityDamageIntensity / fEntityCollisionMass;
            AudioEngine.ReportCollision(entity, this, colPoint.m_nSurfaceTypeB, colPoint.m_nSurfaceTypeA, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
            return true;
        }
        return false;
    }

    if (entity->physicalFlags.bDisableTurnForce)
    {
        CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
        CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

        if (!physicalFlags.bAddMovingCollisionSpeed && m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeA == SURFACE_CAR_MOVINGCOMPONENT)
            vecThisSpeed += thisVehicle->AddMovingCollisionSpeed(vecDistanceToPointFromThis);

        float fThisSpeedDotProduct = DotProduct(vecThisSpeed, colPoint.m_vecNormal);
        float fEntitySpeedDotProduct = DotProduct(entity->m_vecMoveSpeed, colPoint.m_vecNormal);

        CVector vecThisDifference = (vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied);
        CVector vecThisCrossProduct;
        vecThisCrossProduct.Cross(vecThisDifference, colPoint.m_vecNormal);
        float squaredMagnitude = vecThisCrossProduct.SquaredMagnitude();
        float fThisCollisionMass = 0.0f;
        if (physicalFlags.bDisableMoveForce)
        {
            fThisCollisionMass = squaredMagnitude / (fThisMassFactor * m_fTurnMass);
        }
        else
        {
            fThisCollisionMass = squaredMagnitude / (fThisMassFactor * m_fTurnMass) + 1.0f / (fThisMassFactor * m_fMass);
        }

        fThisCollisionMass = 1.0f / fThisCollisionMass;

        float fEntityMass = fEntityMassFactor * entity->m_fMass;
        float fMoveSpeed = (fEntityMass * fEntitySpeedDotProduct + fThisCollisionMass * fThisSpeedDotProduct) / (fEntityMass + fThisCollisionMass);
        float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
        if (fThisMoveSpeedDifference >= 0.0f)
        {
            return false;
        }

        float fThisMoveSpeedElasticity = 0.0f;
        float fEntityMoveSpeedElasticity = 0.0f;

        float fTheElasticity = (entity->m_fElasticity + m_fElasticity) * 0.5f;
        if (m_bHasHitWall)
        {
            fThisMoveSpeedElasticity = fMoveSpeed;
        }
        else
        {
            fThisMoveSpeedElasticity = fMoveSpeed - fTheElasticity * fThisMoveSpeedDifference;
        }

        if (entity->m_bHasHitWall)
        {
            fEntityMoveSpeedElasticity = fMoveSpeed;
        }
        else
        {
            fEntityMoveSpeedElasticity = fMoveSpeed - (fEntitySpeedDotProduct - fMoveSpeed) * fTheElasticity;
        }

        thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisCollisionMass;
        entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityMass);

        CVector vecThisMoveForce = colPoint.m_vecNormal * (thisDamageIntensity / fThisMassFactor);
        CVector vecEntityMoveForce = colPoint.m_vecNormal * (entityDamageIntensity / fEntityMassFactor) * -1.0f;

        if (!physicalFlags.bDisableCollisionForce && !bEntityPedIsStandingOnThis)
        {
            if (vecThisMoveForce.z < 0.0f)
            {
                vecThisMoveForce.z = 0.0f;
            }
            ApplyForce(vecThisMoveForce, vecDistanceToPointFromThis, true);
        }

        if (!entity->physicalFlags.bDisableCollisionForce)
        {
            if (vecEntityMoveForce.z < 0.0f)
            {
                vecEntityMoveForce.z = 0.0f;
                if (fabs(fThisSpeedDotProduct) < 0.01f)
                {
                    vecEntityMoveForce.x *= 0.5f;
                    vecEntityMoveForce.y *= 0.5f;
                    vecEntityMoveForce.z  = 0.0f;
                }
            }
            if (bEntityPedIsStandingOnThis)
            {
                vecEntityMoveForce.x += vecEntityMoveForce.x;
                vecEntityMoveForce.y += vecEntityMoveForce.y;
            }
            if (entity->m_bIsInSafePosition)
            {
                entity->UnsetIsInSafePosition();
            }

            entity->ApplyMoveForce(vecEntityMoveForce);
        }

        float fCollisionImpact1 = thisDamageIntensity / fThisCollisionMass;
        AudioEngine.ReportCollision(this, entity, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);

        fCollisionImpact1 = entityDamageIntensity / fEntityMass;
        AudioEngine.ReportCollision(entity, this, colPoint.m_nSurfaceTypeB, colPoint.m_nSurfaceTypeA, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
    }
    else
    {
        CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
        CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

        if (physicalFlags.bAddMovingCollisionSpeed && m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeA == SURFACE_CAR_MOVINGCOMPONENT)
            vecThisSpeed += thisVehicle->AddMovingCollisionSpeed(vecDistanceToPointFromThis);

        CVector vecDistanceToPoint = colPoint.m_vecPoint - entity->GetPosition();
        CVector vecEntitySpeed = entity->GetSpeed(vecDistanceToPoint);

        if (entity->physicalFlags.bAddMovingCollisionSpeed && entity->m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeB == SURFACE_CAR_MOVINGCOMPONENT)
            vecEntitySpeed += entityVehicle->AddMovingCollisionSpeed(vecDistanceToPoint);

        float fThisSpeedDotProduct = DotProduct(vecThisSpeed, colPoint.m_vecNormal);
        float fEntitySpeedDotProduct = DotProduct(vecEntitySpeed, colPoint.m_vecNormal);

        CVector vecThisDifference = (vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied);
        CVector vecThisCrossProduct;
        vecThisCrossProduct.Cross(vecThisDifference, colPoint.m_vecNormal);
        float squaredMagnitude = vecThisCrossProduct.SquaredMagnitude();

        float fThisCollisionMass = 0.0f;
        if (physicalFlags.bDisableMoveForce)
        {
            fThisCollisionMass = squaredMagnitude / (fThisMassFactor * m_fTurnMass);
        }
        else
        {
            fThisCollisionMass = squaredMagnitude / (fThisMassFactor * m_fTurnMass) + 1.0f / (fThisMassFactor * m_fMass);
        }

        fThisCollisionMass = 1.0f / fThisCollisionMass;

        CVector vecEntityDifference = (vecDistanceToPoint - vecEntityCentreOfMassMultiplied);
        CVector vecEntityCrossProduct;
        vecEntityCrossProduct.Cross(vecEntityDifference, colPoint.m_vecNormal);
        squaredMagnitude = vecEntityCrossProduct.SquaredMagnitude();

        float fEntityCollisionMass = 0.0f;
        if (entity->physicalFlags.bDisableMoveForce)
        {
            fEntityCollisionMass = squaredMagnitude / (fEntityMassFactor * entity->m_fTurnMass);
        }
        else
        {
            fEntityCollisionMass = squaredMagnitude / (fEntityMassFactor * entity->m_fTurnMass) + 1.0f / (fEntityMassFactor * entity->m_fMass);
        }

        fEntityCollisionMass = 1.0f / fEntityCollisionMass;

        float fMoveSpeed = (fEntityCollisionMass * fEntitySpeedDotProduct + fThisCollisionMass * fThisSpeedDotProduct) / (fEntityCollisionMass + fThisCollisionMass);
        float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
        if (fThisMoveSpeedDifference >= 0.0f)
        {
            return false;
        }

        float fThisMoveSpeedElasticity = 0.0f;
        float fEntityMoveSpeedElasticity = 0.0f;
        float fTheElasticity = (entity->m_fElasticity + m_fElasticity) * 0.5f;
        if (m_bHasHitWall)
        {
            fThisMoveSpeedElasticity = fMoveSpeed;
        }
        else
        {
            fThisMoveSpeedElasticity = fMoveSpeed - fTheElasticity * fThisMoveSpeedDifference;
        }

        if (entity->m_bHasHitWall)
        {
            fEntityMoveSpeedElasticity = fMoveSpeed;
        }
        else
        {
            fEntityMoveSpeedElasticity = fMoveSpeed - (fEntitySpeedDotProduct - fMoveSpeed) * fTheElasticity;
        }

        thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisCollisionMass;
        entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityCollisionMass);

        CVector vecThisMoveForce = colPoint.m_vecNormal * (thisDamageIntensity / fThisMassFactor);
        CVector vecEntityMoveForce = colPoint.m_vecNormal * (entityDamageIntensity / fEntityMassFactor) * -1.0f;

        if (m_nType == ENTITY_TYPE_VEHICLE && !m_bHasHitWall && !physicalFlags.bDisableCollisionForce)
        {
            if (colPoint.m_vecNormal.z < 0.7f)
            {
                vecThisMoveForce.z *= 0.3f;
            }

            if (!m_nStatus)
            {
                vecDistanceToPointFromThis *= 0.8f;
            }

            if (CWorld::bNoMoreCollisionTorque)
            {
                CVector vecFrictionForce = vecThisMoveForce * -0.3f;
                ApplyFrictionForce(vecFrictionForce, vecDistanceToPointFromThis);
            }
        }

        if (entity->m_nType == ENTITY_TYPE_VEHICLE && !entity->m_bHasHitWall && !entity->physicalFlags.bDisableCollisionForce)
        {
            if ((colPoint.m_vecNormal.z * -1.0f) < 0.7f)
            {
                vecEntityMoveForce.z *= 0.3f;
            }

            if (!entity->m_nStatus)
            {
                vecDistanceToPoint *= 0.8f;
            }

            if (CWorld::bNoMoreCollisionTorque)
            {
                CVector vecFrictionForce = vecEntityMoveForce * -0.3f;
                entity->ApplyFrictionForce(vecFrictionForce, vecDistanceToPoint);
            }
        }

        if (CCheat::m_aCheatsActive[CHEAT_CARS_FLOAT_AWAY_WHEN_HIT])
        {
            if (FindPlayerVehicle(-1, false) == thisVehicle
                && entity->m_nType == ENTITY_TYPE_VEHICLE && entityVehicle->m_nCreatedBy != MISSION_VEHICLE)
            {
                entity->physicalFlags.bApplyGravity = false;
            }
            if (FindPlayerVehicle(-1, false) == entityVehicle
                && m_nType == ENTITY_TYPE_VEHICLE && thisVehicle->m_nCreatedBy != MISSION_VEHICLE)
            {
                physicalFlags.bApplyGravity = false;
            }
        }

        if (!physicalFlags.bDisableCollisionForce)
        {
            ApplyForce(vecThisMoveForce, vecDistanceToPointFromThis, true);
        }

        if (!entity->physicalFlags.bDisableCollisionForce)
        {
            if (entity->m_bIsInSafePosition)
            {
                entity->UnsetIsInSafePosition();
            }
            entity->ApplyForce(vecEntityMoveForce, vecDistanceToPoint, true);
        }

        float fCollisionImpact1 = thisDamageIntensity / fThisCollisionMass;
        AudioEngine.ReportCollision(this, entity, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);

        fCollisionImpact1 = entityDamageIntensity / fEntityCollisionMass;
        AudioEngine.ReportCollision(entity, this, colPoint.m_nSurfaceTypeB, colPoint.m_nSurfaceTypeA, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
    }
    return true;
}

// 0x54A2C0
bool CPhysical::ApplySoftCollision(CPhysical* physical, CColPoint& colPoint, float& thisDamageIntensity, float& entityDamageIntensity)
{
    auto* entityObject = static_cast<CObject*>(physical);
    auto* entityPed = static_cast<CPed*>(physical);
    auto* entityVehicle = static_cast<CVehicle*>(physical);

    auto* thisObject = static_cast<CObject*>(this);
    auto* thisPed = static_cast<CPed*>(this);
    auto* thisVehicle = static_cast<CVehicle*>(this);

    bool bEntityPedIsStandingOnThis = false;
    bool bThisPedIsStandingOnEntity = false;
    bool bEntityCollisionForceDisabled = false;

    float fThisMassFactor = 0.0f;
    float fEntityMassFactor = 0.0f;
    if (!physical->physicalFlags.bDisableTurnForce || physicalFlags.bDisableMoveForce || physicalFlags.bInfiniteMass)
    {
        fThisMassFactor = 2.0f;
        if (!physicalFlags.bMakeMassTwiceAsBig)
        {
            fThisMassFactor = 1.0f;
        }
    }
    else
    {
        fThisMassFactor = 10.0f;
        if (entityPed->m_standingOnEntity == this) // BUG: Game should be checking if entity is ped or not.
        {
            bEntityPedIsStandingOnThis = true;
        }
    }
    if (!physicalFlags.bDisableTurnForce || physical->physicalFlags.bDisableMoveForce || physical->physicalFlags.bInfiniteMass)
    {
        fEntityMassFactor = 2.0f;
        if (!physical->physicalFlags.bMakeMassTwiceAsBig)
        {
            fEntityMassFactor = 1.0f;
        }
    }
    else
    {
        if (m_nType == ENTITY_TYPE_PED && thisPed->IsPlayer()
            && physical->m_nType == ENTITY_TYPE_VEHICLE
            && (physical->m_nStatus == STATUS_ABANDONED || physical->m_nStatus == STATUS_WRECKED || m_bIsStuck))
        {
            float fTheEntityMass = physical->m_fMass - 2000.0f;
            if (fTheEntityMass < 0.0f)
            {
                fTheEntityMass = 0.0f;
            }
            fEntityMassFactor = 1.0f / (fTheEntityMass * 0.0002f + 1.0f);
        }
        else
        {
            fEntityMassFactor = 10.0f;
        }
        if (m_nType == ENTITY_TYPE_PED && thisPed->m_standingOnEntity == physical)
        {
            bThisPedIsStandingOnEntity = true;
        }
    }

    if (physical->physicalFlags.bDisableCollisionForce && !physical->physicalFlags.bCollidable)
    {
        bEntityCollisionForceDisabled = true;
        bThisPedIsStandingOnEntity = false;
    }

    CVector vecThisCentreOfMassMultiplied;
    CVector vecEntityCentreOfMassMultiplied;

    vecThisCentreOfMassMultiplied = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
    vecThisCentreOfMassMultiplied = Multiply3x3(physical->GetMatrix(), physical->m_vecCentreOfMass);

    if (physicalFlags.bInfiniteMass)
    {
        vecThisCentreOfMassMultiplied = CVector(0.0f, 0.0f, 0.0f);
    }
    if (physical->physicalFlags.bInfiniteMass)
    {
        vecEntityCentreOfMassMultiplied = CVector(0.0f, 0.0f, 0.0f);
    }

    bool bApplyCollisionWithElasticity = false;
    if (!physical->IsStatic() || bEntityCollisionForceDisabled)
    {
        bApplyCollisionWithElasticity = true;
    }
    else
    {
        if (physicalFlags.bDisableTurnForce)
        {
            return ApplySoftCollision(physical, colPoint, thisDamageIntensity);
        }
    }

    CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
    CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

    float fThisSpeedDotProduct = DotProduct(vecThisSpeed, colPoint.m_vecNormal);
    if (!bApplyCollisionWithElasticity && fThisSpeedDotProduct < 0.0f)
    {
        if (physical->m_nType != ENTITY_TYPE_OBJECT)
        {
            if (!physical->physicalFlags.bDisableCollisionForce)
            {
                physical->SetIsStatic(false);
                CWorld::Players[CWorld::PlayerInFocus].m_nHavocCaused += 2;
                CStats::IncrementStat(STAT_COST_OF_PROPERTY_DAMAGED, static_cast<float>(rand() % 30 + 30));
            }
        }
        else
        {
            CVector vecThisDifference = (vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied);
            CVector vecThisCrossProduct;
            vecThisCrossProduct.Cross(vecThisDifference, colPoint.m_vecNormal);
            float squaredMagnitude = vecThisCrossProduct.SquaredMagnitude();

            float fThisCollisionMass = 1.0f / (squaredMagnitude / m_fTurnMass + 1.0f / m_fMass);
            if (!m_bHasHitWall)
            {
                thisDamageIntensity = -((m_fElasticity + 1.0f) * fThisCollisionMass * fThisSpeedDotProduct);
            }
            else
            {
                thisDamageIntensity = fThisCollisionMass * fThisSpeedDotProduct * -1.0f;
            }

            entityDamageIntensity = thisDamageIntensity;

            if (entityObject->m_nColDamageEffect != COL_DAMAGE_EFFECT_NONE && thisDamageIntensity > 20.0f)
            {
                entityObject->ObjectDamage(thisDamageIntensity, &colPoint.m_vecPoint, &colPoint.m_vecNormal, this, WEAPON_UNIDENTIFIED);
                if (!physical->m_bUsesCollision)
                {
                    if (!physicalFlags.bDisableCollisionForce)
                    {
                        CVector vecMoveSpeed = (colPoint.m_vecNormal * 0.2f) * thisDamageIntensity;
                        ApplyForce(vecMoveSpeed, vecDistanceToPointFromThis, true);
                    }

                    float fCollisionImpact1 = thisDamageIntensity / fThisCollisionMass * 0.2f;
                    AudioEngine.ReportCollision(this, physical, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
                    return false;
                }
            }

            float fObjectUprootLimit = entityObject->m_pObjectInfo->m_fUprootLimit;
            if ((thisDamageIntensity > fObjectUprootLimit || m_bIsStuck) && !physical->physicalFlags.bDisableCollisionForce)
            {
                if (IsGlassModel(physical))
                {
                    CGlass::WindowRespondsToCollision(physical, thisDamageIntensity, m_vecMoveSpeed, colPoint.m_vecPoint, false);
                }
                else if (!physical->physicalFlags.bDisableCollisionForce)
                {
                    physical->SetIsStatic(false);
                }

                int32 entityModelIndex = physical->m_nModelIndex;
                if (entityModelIndex != MODEL_FIRE_HYDRANT || entityObject->objectFlags.bIsExploded)
                {
                    if (entityModelIndex != ModelIndices::MI_PARKINGMETER && entityModelIndex != ModelIndices::MI_PARKINGMETER2 || entityObject->objectFlags.bIsExploded)
                    {
                        CBaseModelInfo* pBaseModelInfo = CModelInfo::GetModelInfo(entityModelIndex);
                        if (physical->m_nType != ENTITY_TYPE_OBJECT || pBaseModelInfo->AsAtomicModelInfoPtr())
                        {
                            // nothing
                        }
                        else
                        {
                            entityObject->objectFlags.bIsExploded = true;
                        }
                    }
                    else
                    {
                        CPickups::CreateSomeMoney(physical->GetPosition(), rand() % 100);
                        entityObject->objectFlags.bIsExploded = true;
                    }
                }
                else
                {
                    g_fx.TriggerWaterHydrant(physical->GetPosition());
                    entityObject->objectFlags.bIsExploded = true;
                }

                if (physical->IsStatic())
                {
                    return false;
                }

                if (!physical->physicalFlags.bDisableCollisionForce)
                {
                    physical->AddToMovingList();
                }

                bApplyCollisionWithElasticity = true;
            }
            else
            {
                if (IsGlassModel(physical))
                {
                    CGlass::WindowRespondsToSoftCollision(entityObject, thisDamageIntensity);
                }

                CVector vecThisMoveForce = colPoint.m_vecNormal * thisDamageIntensity;
                if (m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_vecNormal.z < 0.7f)
                {
                    vecThisMoveForce.z *= 0.3f;
                }

                if (!physicalFlags.bDisableCollisionForce)
                {
                    bool bUpdateTorque = m_nType != ENTITY_TYPE_VEHICLE || !CWorld::bNoMoreCollisionTorque;
                    ApplyForce(vecThisMoveForce, vecDistanceToPointFromThis, bUpdateTorque);
                }

                float fCollisionImpact1 = thisDamageIntensity / fThisCollisionMass;
                AudioEngine.ReportCollision(this, physical, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
            }
        }
    }

    if (bApplyCollisionWithElasticity)
    {
        if (physicalFlags.bDisableTurnForce && physical->physicalFlags.bDisableTurnForce)
        {
            float fThisSpeedDotProduct = DotProduct(m_vecMoveSpeed, colPoint.m_vecNormal);
            float fEntitySpeedDotProduct = DotProduct(physical->m_vecMoveSpeed, colPoint.m_vecNormal);

            float fMoveSpeed = fEntitySpeedDotProduct;
            float fThisMass = m_fMass;
            float fEntityMass = physical->m_fMass;
            bool bPedFollowPath = false;
            if (thisPed->m_nPedState == PEDSTATE_FOLLOW_PATH)
            {
                bPedFollowPath = true;
                fMoveSpeed = (fEntityMass * fEntitySpeedDotProduct + fThisMass * fThisSpeedDotProduct + fThisMass * fThisSpeedDotProduct)
                    / (fThisMass + fThisMass + fEntityMass);
            }
            else if (fEntitySpeedDotProduct >= 0.0f)
            {
                fMoveSpeed = 0.0f;
            }

            float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
            if (fThisMoveSpeedDifference >= 0.0f)
            {
                return false;
            }

            float fThisMoveSpeedElasticity = 0.0f;
            float fTheElasticity = (physical->m_fElasticity + m_fElasticity) * 0.5f;
            if (m_bHasHitWall)
            {
                fThisMoveSpeedElasticity = fMoveSpeed;
            }
            else
            {
                fThisMoveSpeedElasticity = fMoveSpeed - fThisMoveSpeedDifference * fTheElasticity;
            }

            thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisMass;
            CVector vecThisMoveForce = colPoint.m_vecNormal * thisDamageIntensity;

            if (!physicalFlags.bDisableCollisionForce)
            {
                ApplyMoveForce(vecThisMoveForce);
            }

            float fCollisionImpact1 = thisDamageIntensity / fThisMass;
            AudioEngine.ReportCollision(this, physical, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
            if (bPedFollowPath)
            {
                float fEntityMoveSpeedDifference = fEntitySpeedDotProduct - fMoveSpeed;
                if (fEntityMoveSpeedDifference < 0.0f)
                {
                    float fEntityMoveSpeedElasticity = 0.0f;
                    if (physical->m_bHasHitWall)
                    {
                        fEntityMoveSpeedElasticity = fMoveSpeed;
                    }
                    else
                    {
                        fEntityMoveSpeedElasticity = fMoveSpeed - fEntityMoveSpeedDifference * fTheElasticity;
                    }

                    entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityMass);
                    CVector vecEntityMoveForce = colPoint.m_vecNormal * entityDamageIntensity * -1.0f;
                    if (!physical->physicalFlags.bDisableCollisionForce)
                    {
                        physical->ApplyMoveForce(vecEntityMoveForce);
                    }

                    float fCollisionImpact1 = entityDamageIntensity / fEntityMass;
                    AudioEngine.ReportCollision(physical, this, colPoint.m_nSurfaceTypeB, colPoint.m_nSurfaceTypeA, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
                }
            }
            return true;
        }

        if (physicalFlags.bDisableTurnForce)
        {
            CVector vecDistanceToPoint = colPoint.m_vecPoint - physical->GetPosition();
            CVector vecEntitySpeed = physical->GetSpeed(vecDistanceToPoint);

            if (!physical->physicalFlags.bAddMovingCollisionSpeed || physical->m_nType != ENTITY_TYPE_VEHICLE
                || colPoint.m_nSurfaceTypeB != SURFACE_CAR_MOVINGCOMPONENT)
            {
                // nothing
            }
            else
            {
                vecEntitySpeed += entityVehicle->AddMovingCollisionSpeed(vecDistanceToPoint);
            }

            float fThisMass = fThisMassFactor * m_fMass;


            float fThisSpeedDotProduct = DotProduct(m_vecMoveSpeed, colPoint.m_vecNormal);
            float fEntitySpeedDotProduct = DotProduct(vecEntitySpeed, colPoint.m_vecNormal);

            CVector vecEntityDifference = (vecDistanceToPoint - vecEntityCentreOfMassMultiplied);
            CVector vecEntityCrossProduct;
            vecEntityCrossProduct.Cross(vecEntityDifference, colPoint.m_vecNormal);
            float squaredMagnitude = vecEntityCrossProduct.SquaredMagnitude();

            float fMoveSpeed = 0.0f;
            float fEntityCollisionMass = 1.0f / (squaredMagnitude / (fEntityMassFactor * physical->m_fTurnMass) + 1.0f / (fEntityMassFactor * physical->m_fMass));
            if (bEntityCollisionForceDisabled)
            {
                fMoveSpeed = fEntitySpeedDotProduct;
            }
            else
            {
                fMoveSpeed = (fEntityCollisionMass * fEntitySpeedDotProduct + fThisMass * fThisSpeedDotProduct) / (fEntityCollisionMass + fThisMass);
            }

            float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
            if (fThisMoveSpeedDifference < 0.0)
            {
                float fThisMoveSpeedElasticity = 0.0f;
                float fEntityMoveSpeedElasticity = 0.0f;
                float fTheElasticity = (physical->m_fElasticity + m_fElasticity) * 0.5f;
                if (m_bHasHitWall)
                {
                    fThisMoveSpeedElasticity = fMoveSpeed;
                }
                else
                {
                    fThisMoveSpeedElasticity = fMoveSpeed - fThisMoveSpeedDifference * fTheElasticity;
                }

                if (physical->m_bHasHitWall)
                {
                    fEntityMoveSpeedElasticity = fMoveSpeed;
                }
                else
                {
                    fEntityMoveSpeedElasticity = fMoveSpeed - (fEntitySpeedDotProduct - fMoveSpeed) * fTheElasticity;
                }

                thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisMass;
                entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityCollisionMass);

                CVector vecThisMoveForce = colPoint.m_vecNormal * (thisDamageIntensity / fThisMassFactor);
                CVector vecEntityMoveForce = (colPoint.m_vecNormal * (entityDamageIntensity / fEntityMassFactor) * -1.0f);

                if (!physicalFlags.bDisableCollisionForce)
                {
                    if (vecThisMoveForce.z < 0.0)
                    {
                        vecThisMoveForce.z = 0.0f;
                    }

                    if (bThisPedIsStandingOnEntity)
                    {
                        vecThisMoveForce.x = vecThisMoveForce.x + vecThisMoveForce.x;
                        vecThisMoveForce.y = vecThisMoveForce.y + vecThisMoveForce.y;
                    }

                    ApplyMoveForce(vecThisMoveForce);
                }

                if (physical->physicalFlags.bDisableCollisionForce || bThisPedIsStandingOnEntity)
                {
                    // nothing
                }
                else
                {
                    physical->ApplyForce(vecEntityMoveForce, vecDistanceToPoint, true);
                }
                float fCollisionImpact1 = thisDamageIntensity / fThisMass;
                AudioEngine.ReportCollision(this, physical, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);

                fCollisionImpact1 = entityDamageIntensity / fEntityCollisionMass;
                AudioEngine.ReportCollision(physical, this, colPoint.m_nSurfaceTypeB, colPoint.m_nSurfaceTypeA, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
                return true;
            }
        }
        else
        {
            if (physical->physicalFlags.bDisableTurnForce)
            {
                CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
                CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

                if (physicalFlags.bAddMovingCollisionSpeed && m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeA == SURFACE_CAR_MOVINGCOMPONENT)
                    vecThisSpeed += thisVehicle->AddMovingCollisionSpeed(vecDistanceToPointFromThis);

                float fThisSpeedDotProduct = DotProduct(vecThisSpeed, colPoint.m_vecNormal);
                float fEntitySpeedDotProduct = DotProduct(physical->m_vecMoveSpeed, colPoint.m_vecNormal);

                CVector vecThisDifference = (vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied);
                CVector vecThisCrossProduct;
                vecThisCrossProduct.Cross(vecThisDifference, colPoint.m_vecNormal);
                float squaredMagnitude = vecThisCrossProduct.SquaredMagnitude();
                float fThisCollisionMass = 1.0f / (squaredMagnitude / (fThisMassFactor * m_fTurnMass) + 1.0f / (fThisMassFactor * m_fMass));

                float fEntityMass = fEntityMassFactor * physical->m_fMass;
                float fMoveSpeed = (fEntityMass * fEntitySpeedDotProduct + fThisCollisionMass * fThisSpeedDotProduct) / (fEntityMass + fThisCollisionMass);
                float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
                if (fThisMoveSpeedDifference < 0.0)
                {
                    float fThisMoveSpeedElasticity = 0.0f;
                    float fEntityMoveSpeedElasticity = 0.0f;

                    float fTheElasticity = (physical->m_fElasticity + m_fElasticity) * 0.5f;
                    if (m_bHasHitWall)
                    {
                        fThisMoveSpeedElasticity = fMoveSpeed;
                    }
                    else
                    {
                        fThisMoveSpeedElasticity = fMoveSpeed - fThisMoveSpeedDifference * fTheElasticity;
                    }
                    if (physical->m_bHasHitWall)
                    {
                        fEntityMoveSpeedElasticity = fMoveSpeed;
                    }
                    else
                    {
                        fEntityMoveSpeedElasticity = fMoveSpeed - (fEntitySpeedDotProduct - fMoveSpeed) * fTheElasticity;
                    }

                    thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisCollisionMass;
                    entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityMass);

                    CVector vecThisMoveForce = colPoint.m_vecNormal * (thisDamageIntensity / fThisMassFactor);
                    CVector vecEntityMoveForce = colPoint.m_vecNormal * (entityDamageIntensity / fEntityMassFactor) * -1.0f;
                    if (!physicalFlags.bDisableCollisionForce && !bEntityPedIsStandingOnThis)
                    {
                        if (vecThisMoveForce.z < 0.0f)
                        {
                            vecThisMoveForce.z = 0.0f;
                        }
                        ApplyForce(vecThisMoveForce, vecDistanceToPointFromThis, true);
                    }

                    if (!physical->physicalFlags.bDisableCollisionForce)
                    {
                        if (vecEntityMoveForce.z < 0.0f)
                        {
                            vecEntityMoveForce.z = 0.0f;
                            if (fabs(fThisSpeedDotProduct) < 0.01f)
                            {
                                vecEntityMoveForce.z = 0.0f;
                                vecEntityMoveForce.x = vecEntityMoveForce.x * 0.5f;
                                vecEntityMoveForce.y = vecEntityMoveForce.y * 0.5f;
                            }
                        }
                        if (bEntityPedIsStandingOnThis)
                        {
                            vecEntityMoveForce.x = vecEntityMoveForce.x + vecEntityMoveForce.x;
                            vecEntityMoveForce.y = vecEntityMoveForce.y + vecEntityMoveForce.y;
                        }

                        physical->ApplyMoveForce(vecEntityMoveForce);
                    }

                    float fCollisionImpact1 = thisDamageIntensity / fThisCollisionMass;
                    AudioEngine.ReportCollision(this, physical, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);

                    fCollisionImpact1 = entityDamageIntensity / fEntityMass;
                    AudioEngine.ReportCollision(physical, this, colPoint.m_nSurfaceTypeB, colPoint.m_nSurfaceTypeA, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
                    return true;
                }
            }
            else
            {
                CVector vecDistanceToPointFromThis = colPoint.m_vecPoint - GetPosition();
                CVector vecThisSpeed = GetSpeed(vecDistanceToPointFromThis);

                if (physicalFlags.bAddMovingCollisionSpeed && m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeA == SURFACE_CAR_MOVINGCOMPONENT)
                    vecThisSpeed += thisVehicle->AddMovingCollisionSpeed(vecDistanceToPointFromThis);

                CVector vecDistanceToPoint = colPoint.m_vecPoint - physical->GetPosition();
                CVector vecEntitySpeed = physical->GetSpeed(vecDistanceToPoint);

                if (physical->physicalFlags.bAddMovingCollisionSpeed && physical->m_nType == ENTITY_TYPE_VEHICLE && colPoint.m_nSurfaceTypeB == SURFACE_CAR_MOVINGCOMPONENT)
                    vecEntitySpeed += entityVehicle->AddMovingCollisionSpeed(vecDistanceToPoint);

                float fThisSpeedDotProduct = DotProduct(vecThisSpeed, colPoint.m_vecNormal);
                float fEntitySpeedDotProduct = DotProduct(vecEntitySpeed, colPoint.m_vecNormal);

                CVector vecThisDifference = (vecDistanceToPointFromThis - vecThisCentreOfMassMultiplied);
                CVector vecThisCrossProduct;
                vecThisCrossProduct.Cross(vecThisDifference, colPoint.m_vecNormal);
                float squaredMagnitude = vecThisCrossProduct.SquaredMagnitude();
                float fThisCollisionMass = 1.0f / (squaredMagnitude / (fThisMassFactor * m_fTurnMass) + 1.0f / (fThisMassFactor * m_fMass));

                CVector vecEntityDifference = (vecDistanceToPoint - vecEntityCentreOfMassMultiplied);
                CVector vecEntityCrossProduct;
                vecEntityCrossProduct.Cross(vecEntityDifference, colPoint.m_vecNormal);
                squaredMagnitude = vecEntityCrossProduct.SquaredMagnitude();
                float fEntityCollisionMass = 1.0f / (squaredMagnitude / (fEntityMassFactor * physical->m_fTurnMass) + 1.0f / (fEntityMassFactor * physical->m_fMass));

                float fMoveSpeed = (fEntityCollisionMass * fEntitySpeedDotProduct + fThisCollisionMass * fThisSpeedDotProduct) / (fEntityCollisionMass + fThisCollisionMass);
                float fThisMoveSpeedDifference = fThisSpeedDotProduct - fMoveSpeed;
                if (fThisMoveSpeedDifference < 0.0f)
                {
                    float fThisMoveSpeedElasticity = 0.0f;
                    float fEntityMoveSpeedElasticity = 0.0f;

                    float fTheElasticity = (physical->m_fElasticity + m_fElasticity) * 0.5f;
                    if (m_bHasHitWall)
                    {
                        fThisMoveSpeedElasticity = fMoveSpeed;
                    }
                    else
                    {
                        fThisMoveSpeedElasticity = fMoveSpeed - fThisMoveSpeedDifference * fTheElasticity;
                    }
                    if (physical->m_bHasHitWall)
                    {
                        fEntityMoveSpeedElasticity = fMoveSpeed;
                    }
                    else
                    {
                        fEntityMoveSpeedElasticity = fMoveSpeed - (fEntitySpeedDotProduct - fMoveSpeed) * fTheElasticity;
                    }

                    thisDamageIntensity = (fThisMoveSpeedElasticity - fThisSpeedDotProduct) * fThisCollisionMass;
                    entityDamageIntensity = -((fEntityMoveSpeedElasticity - fEntitySpeedDotProduct) * fEntityCollisionMass);

                    CVector vecThisMoveForce = colPoint.m_vecNormal * (thisDamageIntensity / fThisMassFactor);
                    CVector vecEntityMoveForce = colPoint.m_vecNormal * (entityDamageIntensity / fEntityMassFactor) * -1.0f;

                    if (m_nType == ENTITY_TYPE_VEHICLE && !m_bHasHitWall)
                    {
                        if (colPoint.m_vecNormal.z < 0.7f)
                        {
                            vecThisMoveForce.z *= 0.3f;
                        }

                        if (!m_nStatus)
                        {
                            vecDistanceToPointFromThis *= 0.8f;
                        }

                        if (CWorld::bNoMoreCollisionTorque)
                        {
                            CVector vecFrictionForce = vecThisMoveForce * -0.3f;
                            ApplyFrictionForce(vecFrictionForce, vecDistanceToPointFromThis);
                        }
                    }

                    if (physical->m_nType == ENTITY_TYPE_VEHICLE && !physical->m_bHasHitWall)
                    {
                        if ((colPoint.m_vecNormal.z * -1.0f) < 0.7f)
                        {
                            vecEntityMoveForce.z *= 0.3f;
                        }

                        if (!physical->m_nStatus)
                        {
                            vecDistanceToPoint *= 0.8f;

                        }
                        if (CWorld::bNoMoreCollisionTorque)
                        {
                            CVector vecFrictionForce = vecEntityMoveForce * -0.3f;
                            physical->ApplyFrictionForce(vecFrictionForce, vecDistanceToPoint);
                        }
                    }
                    if (!physicalFlags.bDisableCollisionForce)
                    {
                        ApplyForce(vecThisMoveForce, vecDistanceToPointFromThis, true);
                    }

                    if (physical->physicalFlags.bDisableCollisionForce)
                    {
                        // nothing
                    }
                    else
                    {
                        if (physical->m_bIsInSafePosition)
                        {
                            physical->m_vecMoveSpeed *= -1.0f;
                            physical->m_vecTurnSpeed *= -1.0f;
                            physical->ApplySpeed();

                            physical->m_vecMoveSpeed *= -1.0f;
                            physical->m_vecTurnSpeed *= -1.0f;
                            physical->m_bIsInSafePosition = false;
                        }

                        physical->ApplyForce(vecEntityMoveForce, vecDistanceToPoint, true);
                    }

                    float fCollisionImpact1 = thisDamageIntensity / fThisCollisionMass;
                    AudioEngine.ReportCollision(this, physical, colPoint.m_nSurfaceTypeA, colPoint.m_nSurfaceTypeB, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);

                    fCollisionImpact1 = entityDamageIntensity / fEntityCollisionMass;
                    AudioEngine.ReportCollision(physical, this, colPoint.m_nSurfaceTypeB, colPoint.m_nSurfaceTypeA, colPoint.m_vecPoint, &colPoint.m_vecNormal, fCollisionImpact1, 1.0f, false, false);
                    return true;
                }
            }
        }
        return false;
    }
    return true;
}

// 0x54BA60
bool CPhysical::ProcessCollisionSectorList(int32 sectorX, int32 sectorY)
{
    static CColPoint colPoints[32];

    bool bResult = false;

    bool bCollisionDisabled = false;
    bool bCollidedEntityCollisionIgnored = false;
    bool bCollidedEntityUnableToMove = false;
    bool bThisOrCollidedEntityStuck = false;

    float fThisDamageIntensity = -1.0f;
    float fEntityDamageIntensity = -1.0f;
    float fThisMaxDamageIntensity = 0.0f;
    float fEntityMaxDamageIntensity = 0.0f;

    CBaseModelInfo* pModelInfo = CModelInfo::GetModelInfo(m_nModelIndex);
    float fBoundingSphereRadius = pModelInfo->GetColModel()->GetBoundRadius();

    CVector vecBoundCentre;
    GetBoundCentre(&vecBoundCentre);

    CSector* sector = GetSector(sectorX, sectorY);
    CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);

    int32 scanListIndex = 4;
    do {
        CPtrListDoubleLink* doubleLinkList = nullptr;
        --scanListIndex;
        switch (scanListIndex) {
        case 0:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_PEDS];
            break;
        case 1:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_OBJECTS];
            break;
        case 2:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_VEHICLES];
            break;
        case 3:
            doubleLinkList = &sector->m_buildings;
            break;
        }
        CPtrNodeDoubleLink* node = doubleLinkList->GetNode();
        if (node) {
            CEntity* entity = nullptr;

            CPhysical* physicalEntity = nullptr;
            CObject* entityObject = nullptr;
            CPed* entityPed = nullptr;
            CVehicle* entityVehicle = nullptr;

            CObject* thisObject = nullptr;
            CPed* thisPed = nullptr;
            CVehicle* thisVehicle = nullptr;

            while (node) {
                entity = (CEntity*)node->pItem;
                node = node->pNext;

                physicalEntity = static_cast<CPhysical*>(entity);
                entityObject = static_cast<CObject*>(entity);
                entityPed = static_cast<CPed*>(entity);
                entityVehicle = static_cast<CVehicle*>(entity);

                thisObject = static_cast<CObject*>(this);
                thisPed = static_cast<CPed*>(this);
                thisVehicle = static_cast<CVehicle*>(this);

                if (!entity->m_bUsesCollision || physicalEntity == this || entity->m_nScanCode == CWorld::ms_nCurrentScanCode) {
                    continue;
                }

                if (!entity->GetIsTouching(vecBoundCentre, fBoundingSphereRadius)) {
                    if (m_pEntityIgnoredCollision == entity && m_pAttachedTo != entity) {
                        m_pEntityIgnoredCollision = nullptr;
                    }

                    if (entity->m_nType > ENTITY_TYPE_BUILDING && entity->m_nType < ENTITY_TYPE_DUMMY && physicalEntity->m_pEntityIgnoredCollision == this &&
                        physicalEntity->m_pAttachedTo != this) {
                        physicalEntity->m_pEntityIgnoredCollision = nullptr;
                    }
                    continue;
                }

                bCollisionDisabled = false;
                bCollidedEntityCollisionIgnored = false;
                bCollidedEntityUnableToMove = false;
                bThisOrCollidedEntityStuck = false;

                physicalFlags.b13 = false;

                if (entity->m_nType == ENTITY_TYPE_BUILDING) {
                    bCollidedEntityCollisionIgnored = false;
                    if (physicalFlags.bInfiniteMass && m_bIsStuck) {
                        bThisOrCollidedEntityStuck = true;
                    }

                    if (physicalFlags.bDisableCollisionForce && (m_nType != ENTITY_TYPE_VEHICLE || thisVehicle->m_vehicleSubType == VEHICLE_TRAIN)) {
                        bCollisionDisabled = true;
                    } else {
                        if (m_pAttachedTo && m_pAttachedTo->m_nType > ENTITY_TYPE_BUILDING && m_pAttachedTo->m_nType < ENTITY_TYPE_DUMMY &&
                            m_pAttachedTo->physicalFlags.bDisableCollisionForce) {
                            bCollisionDisabled = true;
                        } else if (m_pEntityIgnoredCollision == entity) {
                            bCollisionDisabled = true;
                        } else if (!physicalFlags.bDisableZ || physicalFlags.bApplyGravity) {
                            if (physicalFlags.bDontCollideWithFlyers) {
                                if (m_nStatus) {
                                    if (m_nStatus != STATUS_HELI && entity->DoesNotCollideWithFlyers()) {
                                        bCollisionDisabled = true;
                                    }
                                }
                            }
                        } else {
                            bCollisionDisabled = true;
                        }
                    }
                } else {
                    SpecialEntityPreCollisionStuff(entity, false, &bCollisionDisabled, &bCollidedEntityCollisionIgnored, &bCollidedEntityUnableToMove, &bThisOrCollidedEntityStuck);
                }

                if (!m_bUsesCollision || bCollidedEntityCollisionIgnored || bCollisionDisabled) {
                    entity->m_nScanCode = CWorld::ms_nCurrentScanCode;
                    if (!bCollisionDisabled) // if collision is enabled then
                    {
                        int32 totalColPointsToProcess = ProcessEntityCollision(physicalEntity, &colPoints[0]);
                        if (physicalFlags.b17 && !bCollidedEntityCollisionIgnored && totalColPointsToProcess > 0) {
                            return true;
                        }
                        if (!totalColPointsToProcess && m_pEntityIgnoredCollision == entity && this == FindPlayerPed(-1)) {
                            m_pEntityIgnoredCollision = nullptr;
                        }
                    }
                    continue;
                }

                if (entity->m_nType == ENTITY_TYPE_BUILDING || physicalEntity->physicalFlags.bCollidable || bCollidedEntityUnableToMove) {
                    entity->m_nScanCode = CWorld::ms_nCurrentScanCode;

                    int32 totalAcceptableColPoints = 0;
                    float fThisMaxDamageIntensity = 0.0f;
                    CVector vecMoveSpeed = CVector(0.0f, 0.0f, 0.0f);
                    CVector vecTurnSpeed = CVector(0.0f, 0.0f, 0.0f);

                    int32 totalColPointsToProcess = ProcessEntityCollision(physicalEntity, &colPoints[0]);
                    if (totalColPointsToProcess > 0) {
                        if (m_bHasContacted) {
                            if (totalColPointsToProcess > 0) {
                                for (int32 colPointIndex = 0; colPointIndex < totalColPointsToProcess; colPointIndex++) {
                                    CColPoint* colPoint = &colPoints[colPointIndex];
                                    if (bThisOrCollidedEntityStuck || (colPoint->m_nPieceTypeA >= 13 && colPoint->m_nPieceTypeA <= 16)) {
                                        ApplySoftCollision(entity, *colPoint, fThisDamageIntensity);
                                    } else if (ApplyCollisionAlt(physicalEntity, *colPoint, fThisDamageIntensity, vecMoveSpeed, vecTurnSpeed)) {
                                        ++totalAcceptableColPoints;
                                        if (fThisDamageIntensity > fThisMaxDamageIntensity) {
                                            fThisMaxDamageIntensity = fThisDamageIntensity;
                                        }

                                        if (m_nType == ENTITY_TYPE_VEHICLE) {
                                            if (thisVehicle->m_vehicleType != VEHICLE_BOAT || colPoint->m_nSurfaceTypeB != SURFACE_WOOD_SOLID) {
                                                SetDamagedPieceRecord(fThisDamageIntensity, physicalEntity, *colPoint, 1.0f);
                                            }
                                        } else {
                                            SetDamagedPieceRecord(fThisDamageIntensity, physicalEntity, *colPoint, 1.0f);
                                        }
                                    }
                                }
                            }
                        } else {
                            for (int32 colPointIndex = 0; colPointIndex < totalColPointsToProcess; colPointIndex++) {
                                CColPoint* colPoint = &colPoints[colPointIndex];
                                if (bThisOrCollidedEntityStuck || (colPoint->m_nPieceTypeA >= 13 && colPoint->m_nPieceTypeA <= 16)) {
                                    if (ApplySoftCollision(entity, *colPoint, fThisDamageIntensity) &&
                                        (colPoint->m_nSurfaceTypeA != SURFACE_WHEELBASE || colPoint->m_nSurfaceTypeB != SURFACE_WHEELBASE)) {
                                        float fSurfaceFriction = g_surfaceInfos->GetAdhesiveLimit(colPoint);
                                        if (ApplyFriction(fSurfaceFriction, *colPoint)) {
                                            m_bHasContacted = true;
                                        }
                                        continue;
                                    }
                                } else if (ApplyCollisionAlt(physicalEntity, *colPoint, fThisDamageIntensity, vecMoveSpeed, vecTurnSpeed)) {
                                    ++totalAcceptableColPoints;
                                    if (fThisDamageIntensity > fThisMaxDamageIntensity) {
                                        fThisMaxDamageIntensity = fThisDamageIntensity;
                                    }

                                    float fSurfaceFirction = g_surfaceInfos->GetAdhesiveLimit(colPoint);
                                    float fFriction = fSurfaceFirction / totalColPointsToProcess;
                                    if (m_nType != ENTITY_TYPE_VEHICLE) {
                                        fFriction *= 150.0f * fThisDamageIntensity;
                                        SetDamagedPieceRecord(fThisDamageIntensity, entity, *colPoint, 1.0f);
                                        if (ApplyFriction(fFriction, *colPoint)) {
                                            m_bHasContacted = true;
                                        }
                                        continue;
                                    }
                                    if (thisVehicle->m_vehicleType != VEHICLE_BOAT || colPoint->m_nSurfaceTypeB != SURFACE_WOOD_SOLID) {
                                        SetDamagedPieceRecord(fThisDamageIntensity, entity, *colPoint, 1.0f);
                                    } else {
                                        fFriction = 0.0f;
                                    }

                                    if (m_nModelIndex == MODEL_RCBANDIT) {
                                        fFriction *= 0.2f;
                                    } else {
                                        if (thisVehicle->m_vehicleType == VEHICLE_BOAT) {
                                            if (colPoint->m_vecNormal.z > 0.6f) {
                                                if (g_surfaceInfos->GetAdhesionGroup(colPoint->m_nSurfaceTypeB) == ADHESION_GROUP_LOOSE ||
                                                    g_surfaceInfos->GetAdhesionGroup(colPoint->m_nSurfaceTypeB) == ADHESION_GROUP_SAND) {
                                                    fFriction *= 3.0f;
                                                }
                                            } else {
                                                fFriction = 0.0f;
                                            }
                                        }

                                        if (thisVehicle->m_vehicleSubType != VEHICLE_TRAIN) {
                                            if (m_nStatus == STATUS_WRECKED) {
                                                fFriction *= 3.0f;
                                            } else {
                                                if (GetUp().z > 0.3f && m_vecMoveSpeed.SquaredMagnitude() < 0.02f && m_vecTurnSpeed.SquaredMagnitude() < 0.01f) {
                                                    fFriction = 0.0f;
                                                } else {
                                                    if (m_nStatus != STATUS_ABANDONED && DotProduct(&colPoint->m_vecNormal, &GetUp()) >= 0.707f) {
                                                    } else {
                                                        fFriction = 150.0f / m_fMass * fFriction * fThisDamageIntensity;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    if (m_nType == ENTITY_TYPE_VEHICLE && thisVehicle->m_vehicleSubType == VEHICLE_TRAIN) {
                                        fFriction = fFriction + fFriction;
                                    }
                                    if (ApplyFriction(fFriction, *colPoint)) {
                                        m_bHasContacted = true;
                                    }
                                }
                            }
                        }
                    }

                    if (totalAcceptableColPoints) {
                        float fSpeedFactor = 1.0f / totalAcceptableColPoints;
                        m_vecMoveSpeed += vecMoveSpeed * fSpeedFactor;
                        m_vecTurnSpeed += vecTurnSpeed * fSpeedFactor;
                        if (!CWorld::bNoMoreCollisionTorque) {
                            if (!m_nStatus && m_nType == ENTITY_TYPE_VEHICLE) {
                                float fThisMoveSpeedX = m_vecMoveSpeed.x;
                                if (m_vecMoveSpeed.x < 0.0f) {
                                    fThisMoveSpeedX = -fThisMoveSpeedX;
                                }

                                if (fThisMoveSpeedX > 0.2f) {
                                    float fThisMoveSpeedY = m_vecMoveSpeed.y;
                                    if (m_vecMoveSpeed.y < 0.0f) {
                                        fThisMoveSpeedY = -fThisMoveSpeedY;
                                    }
                                    if (fThisMoveSpeedY > 0.2f) {
                                        if (!physicalFlags.bSubmergedInWater) {
                                            m_vecFrictionMoveSpeed.x -= vecMoveSpeed.x * 0.3f / (float)totalColPointsToProcess;
                                            m_vecFrictionMoveSpeed.y -= vecMoveSpeed.y * 0.3f / (float)totalColPointsToProcess;
                                            m_vecFrictionTurnSpeed += (vecTurnSpeed * -0.3f) / (float)totalColPointsToProcess;
                                        }
                                    }
                                }
                            }
                        }

                        if (entity->m_nType == ENTITY_TYPE_OBJECT && entityObject->m_nColDamageEffect && fThisMaxDamageIntensity > 20.0f) {
                            entityObject->ObjectDamage(fThisMaxDamageIntensity, &colPoints[0].m_vecPoint, &CPhysical::fxDirection, this, WEAPON_UNIDENTIFIED);
                        }
                        if (!CWorld::bSecondShift) {
                            return true;
                        }

                        bResult = true;
                    }
                } else {
                    entity->m_nScanCode = CWorld::ms_nCurrentScanCode;

                    int32 totalAcceptableColPoints = 0;
                    int32 totalColPointsToProcess = ProcessEntityCollision(physicalEntity, &colPoints[0]);
                    if (totalColPointsToProcess <= 0)
                        continue;

                    fThisMaxDamageIntensity = 0.0f;
                    fEntityMaxDamageIntensity = 0.0f;
                    if (m_bHasContacted && entity->m_bHasContacted) {
                        if (totalColPointsToProcess > 0) {
                            for (int32 colPointIndex4 = 0; colPointIndex4 < totalColPointsToProcess; colPointIndex4++) {
                                CColPoint* colPoint2 = &colPoints[colPointIndex4];
                                if (bThisOrCollidedEntityStuck || (colPoint2->m_nPieceTypeA >= 13 && colPoint2->m_nPieceTypeA <= 16) ||
                                    (colPoint2->m_nPieceTypeB >= 13 && colPoint2->m_nPieceTypeB <= 16)) {
                                    ++totalAcceptableColPoints;
                                    ApplySoftCollision(physicalEntity, *colPoint2, fThisDamageIntensity, fEntityDamageIntensity);
                                } else {
                                    if (ApplyCollision(entity, *colPoint2, fThisDamageIntensity, fEntityDamageIntensity)) {
                                        if (fThisDamageIntensity > fThisMaxDamageIntensity) {
                                            fThisMaxDamageIntensity = fThisDamageIntensity;
                                        }
                                        if (fEntityDamageIntensity > fEntityMaxDamageIntensity) {
                                            fEntityMaxDamageIntensity = fEntityDamageIntensity;
                                        }

                                        SetDamagedPieceRecord(fThisDamageIntensity, physicalEntity, *colPoint2, 1.0f);
                                        physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint2, -1.0f);
                                    }
                                }
                            }
                        }
                    } else if (m_bHasContacted) {
                        m_bHasContacted = false;
                        CVector vecThisFrictionMoveSpeed = m_vecFrictionMoveSpeed;
                        CVector vecThisFrictionTurnSpeed = m_vecFrictionTurnSpeed;
                        ResetFrictionMoveSpeed();
                        ResetFrictionTurnSpeed();
                        if (totalColPointsToProcess > 0) {
                            for (int32 colPointIndex1 = 0; colPointIndex1 < totalColPointsToProcess; colPointIndex1++) {
                                CColPoint* colPoint1 = &colPoints[colPointIndex1];
                                if (bThisOrCollidedEntityStuck || (colPoint1->m_nPieceTypeA >= 13 && colPoint1->m_nPieceTypeA <= 16) ||
                                    (colPoint1->m_nPieceTypeB >= 13 && colPoint1->m_nPieceTypeB <= 16)) {
                                    ++totalAcceptableColPoints;
                                    ApplySoftCollision(physicalEntity, *colPoint1, fThisDamageIntensity, fEntityDamageIntensity);
                                    if (colPoint1->m_nPieceTypeB >= 13 && colPoint1->m_nPieceTypeB <= 16) {
                                        physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint1, -1.0f);
                                    }
                                } else if (ApplyCollision(physicalEntity, *colPoint1, fThisDamageIntensity, fEntityDamageIntensity)) {
                                    if (fThisDamageIntensity > fThisMaxDamageIntensity) {
                                        fThisMaxDamageIntensity = fThisDamageIntensity;
                                    }
                                    if (fEntityDamageIntensity > fEntityMaxDamageIntensity) {
                                        fEntityMaxDamageIntensity = fEntityDamageIntensity;
                                    }

                                    SetDamagedPieceRecord(fThisDamageIntensity, physicalEntity, *colPoint1, 1.0f);
                                    physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint1, -1.0f);

                                    float fSurfaceFriction1 = g_surfaceInfos->GetAdhesiveLimit(colPoint1);
                                    float fFriction3 = fSurfaceFriction1 / totalColPointsToProcess;
                                    if (m_nType == ENTITY_TYPE_VEHICLE && entity->m_nType == ENTITY_TYPE_VEHICLE &&
                                        (m_vecMoveSpeed.SquaredMagnitude() > 0.02f || m_vecTurnSpeed.SquaredMagnitude() > 0.01f)) {
                                        fFriction3 *= 1.0f * fThisDamageIntensity;
                                    }

                                    if (entity->IsStatic()) {
                                        if (ApplyFriction(fFriction3, *colPoint1)) {
                                            m_bHasContacted = true;
                                        }
                                    } else if (ApplyFriction(physicalEntity, fFriction3, *colPoint1)) {
                                        m_bHasContacted = true;
                                        entity->m_bHasContacted = true;
                                    }
                                }
                            }
                        }

                        if (!m_bHasContacted) {
                            m_bHasContacted = true;
                            m_vecFrictionMoveSpeed = vecThisFrictionMoveSpeed;
                            m_vecFrictionTurnSpeed = vecThisFrictionTurnSpeed;
                        }
                    } else {
                        if (entity->m_bHasContacted) {
                            entity->m_bHasContacted = false;
                            CVector vecEntityMoveSpeed = physicalEntity->m_vecFrictionMoveSpeed;
                            CVector vecEntityFrictionTurnSpeed = physicalEntity->m_vecFrictionTurnSpeed;
                            physicalEntity->ResetFrictionMoveSpeed();
                            physicalEntity->ResetFrictionTurnSpeed();

                            if (totalColPointsToProcess > 0) {
                                for (int32 colPointIndex3 = 0; colPointIndex3 < totalColPointsToProcess; colPointIndex3++) {
                                    CColPoint* colPoint4 = &colPoints[colPointIndex3];
                                    if (bThisOrCollidedEntityStuck || (colPoint4->m_nPieceTypeA >= 13 && colPoint4->m_nPieceTypeA <= 16) ||
                                        (colPoint4->m_nPieceTypeB >= 13 && colPoint4->m_nPieceTypeB <= 16)) {
                                        ++totalAcceptableColPoints;
                                        ApplySoftCollision(physicalEntity, *colPoint4, fThisDamageIntensity, fEntityDamageIntensity);
                                        if (colPoint4->m_nPieceTypeB >= 13 && colPoint4->m_nPieceTypeB <= 16) {
                                            physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint4, -1.0f);
                                        }
                                    } else if (ApplyCollision(physicalEntity, *colPoint4, fThisDamageIntensity, fEntityDamageIntensity)) {
                                        if (fThisDamageIntensity > fThisMaxDamageIntensity) {
                                            fThisMaxDamageIntensity = fThisDamageIntensity;
                                        }

                                        if (fEntityDamageIntensity > fEntityMaxDamageIntensity) {
                                            fEntityMaxDamageIntensity = fEntityDamageIntensity;
                                        }

                                        SetDamagedPieceRecord(fThisDamageIntensity, physicalEntity, *colPoint4, 1.0f);
                                        physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint4, -1.0f);

                                        float fSurfaceFriction1 = g_surfaceInfos->GetAdhesiveLimit(colPoint4);

                                        float fFriction2 = fSurfaceFriction1 / totalColPointsToProcess;
                                        if (m_nType == ENTITY_TYPE_VEHICLE && entity->m_nType == ENTITY_TYPE_VEHICLE &&
                                            (m_vecMoveSpeed.SquaredMagnitude() > 0.02f || m_vecTurnSpeed.SquaredMagnitude() > 0.01f)) {
                                            fFriction2 *= 1.0f * fThisDamageIntensity;
                                        }

                                        if (entity->IsStatic()) {
                                            if (ApplyFriction(fFriction2, *colPoint4)) {
                                                m_bHasContacted = true;
                                            }
                                        } else if (ApplyFriction(physicalEntity, fFriction2, *colPoint4)) {
                                            m_bHasContacted = true;
                                            entity->m_bHasContacted = true;
                                        }
                                    }
                                }
                            }

                            if (!entity->m_bHasContacted) {
                                entity->m_bHasContacted = true;
                                physicalEntity->m_vecFrictionMoveSpeed = vecEntityMoveSpeed;
                                physicalEntity->m_vecFrictionTurnSpeed = vecEntityFrictionTurnSpeed;
                            }
                        } else if (totalColPointsToProcess > 0) {
                            for (int32 colPointIndex2 = 0; colPointIndex2 < totalColPointsToProcess; colPointIndex2++) {
                                CColPoint* colPoint3 = &colPoints[colPointIndex2];
                                if (bThisOrCollidedEntityStuck || (colPoint3->m_nPieceTypeA >= 13 && colPoint3->m_nPieceTypeA <= 16) ||
                                    (colPoint3->m_nPieceTypeA >= 13 && colPoint3->m_nPieceTypeA <= 16) // BUG: I think it should be m_nPieceTypeB
                                ) {
                                    ++totalAcceptableColPoints;
                                    ApplySoftCollision(physicalEntity, *colPoint3, fThisDamageIntensity, fEntityDamageIntensity);
                                    if (colPoint3->m_nPieceTypeB >= 13 && colPoint3->m_nPieceTypeB <= 16) {
                                        physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint3, -1.0f);
                                    }
                                } else if (ApplyCollision(physicalEntity, *colPoint3, fThisDamageIntensity, fEntityDamageIntensity)) {
                                    if (fThisDamageIntensity > fThisMaxDamageIntensity) {
                                        fThisMaxDamageIntensity = fThisDamageIntensity;
                                    }

                                    if (fEntityDamageIntensity > fEntityMaxDamageIntensity) {
                                        fEntityMaxDamageIntensity = fEntityDamageIntensity;
                                    }

                                    SetDamagedPieceRecord(fThisDamageIntensity, physicalEntity, *colPoint3, 1.0f);
                                    physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint3, -1.0f);

                                    float fSurfaceFirction2 = g_surfaceInfos->GetAdhesiveLimit(colPoint3);
                                    float fFriction1 = fSurfaceFirction2 / totalColPointsToProcess;
                                    if (m_nType == ENTITY_TYPE_VEHICLE && entity->m_nType == ENTITY_TYPE_VEHICLE &&
                                        (m_vecMoveSpeed.SquaredMagnitude() > 0.02f || m_vecTurnSpeed.SquaredMagnitude() > 0.01f)) {
                                        fFriction1 *= 1.0f * fThisDamageIntensity;
                                    }

                                    if (entity->IsStatic()) {
                                        if (ApplyFriction(fFriction1, *colPoint3)) {
                                            m_bHasContacted = true;
                                        }
                                    } else if (ApplyFriction(physicalEntity, fFriction1, *colPoint3)) {
                                        m_bHasContacted = true;
                                        entity->m_bHasContacted = true;
                                    }
                                }
                            }
                        }
                    }

                    if (entity->m_nType == ENTITY_TYPE_PED && m_nType == ENTITY_TYPE_VEHICLE) {
                        float fThisMoveSpeedDot = m_vecMoveSpeed.SquaredMagnitude();
                        if (!entityPed->IsPlayer() || entity->m_bIsStuck && m_vecMoveSpeed.SquaredMagnitude() > 0.0025f) {
                            entityPed->KillPedWithCar(static_cast<CVehicle*>(this), fEntityMaxDamageIntensity, false);
                        }
                    } else if (m_nType == ENTITY_TYPE_PED && entity->m_nType == ENTITY_TYPE_VEHICLE && entityVehicle->m_vehicleSubType == VEHICLE_TRAIN &&
                               (DotProduct(&entityVehicle->m_vecMoveSpeed, &m_vecLastCollisionImpactVelocity) > 0.2f ||
                                thisPed->bFallenDown && entityVehicle->m_vecMoveSpeed.SquaredMagnitude() > 0.0005f)) {
                        float fDamageIntensity = fThisMaxDamageIntensity + fThisMaxDamageIntensity;
                        thisPed->KillPedWithCar(entityVehicle, fDamageIntensity, false);
                    } else if (entity->IsObject() && IsVehicle() && entity->m_bUsesCollision) {
                        if (entityObject->m_nColDamageEffect && fEntityMaxDamageIntensity > 20.0f) {
                            entityObject->ObjectDamage(fEntityMaxDamageIntensity, &colPoints[0].m_vecPoint, &CPhysical::fxDirection, this, WEAPON_RUNOVERBYCAR);
                        } else {
                            if (entityObject->m_nColDamageEffect >= COL_DAMAGE_EFFECT_SMASH_COMPLETELY) {
                                CBaseModelInfo* pEntityModelInfo = CModelInfo::GetModelInfo(entity->m_nModelIndex);
                                CColModel* colModel = pEntityModelInfo->GetColModel();
                                CVector boundBoxPos = entity->GetMatrix() * colModel->m_boundBox.GetSize();

                                bool bObjectDamage = false;
                                if (GetPosition().z > boundBoxPos.z) {
                                    bObjectDamage = true;
                                } else {
                                    CMatrix invertedMatrix;
                                    invertedMatrix = Invert(*m_matrix, invertedMatrix);
                                    if ((invertedMatrix * boundBoxPos).z < 0.0f)
                                        bObjectDamage = true;
                                }
                                if (bObjectDamage)
                                    entityObject->ObjectDamage(50.0f, &colPoints[0].m_vecPoint, &CPhysical::fxDirection, this, WEAPON_RUNOVERBYCAR);
                            }
                        }
                    } else if (IsObject() && entity->IsVehicle() && m_bUsesCollision) {
                        if (thisObject->m_nColDamageEffect && fEntityMaxDamageIntensity > 20.0f) {
                            thisObject->ObjectDamage(fEntityMaxDamageIntensity, &colPoints[0].m_vecPoint, &CPhysical::fxDirection, entity, WEAPON_RUNOVERBYCAR);
                        } else {
                            // BUG: entity is a vehicle here, but we are treating it as an object?
                            if (entityObject->m_nColDamageEffect >= COL_DAMAGE_EFFECT_SMASH_COMPLETELY) {

                                CColModel* colModel = pModelInfo->GetColModel();
                                CVector boundBoxPos = (*m_matrix) * colModel->m_boundBox.GetSize();

                                bool bObjectDamage = false;
                                if (boundBoxPos.z < entity->GetPosition().z) {
                                    bObjectDamage = true;
                                } else {
                                    CMatrix invertedMatrix;
                                    invertedMatrix = Invert(entity->GetMatrix(), invertedMatrix);
                                    if ((invertedMatrix * boundBoxPos).z < 0.0f)
                                        bObjectDamage = true;
                                }

                                if (bObjectDamage)
                                    thisObject->ObjectDamage(50.0f, &colPoints[0].m_vecPoint, &CPhysical::fxDirection, entity, WEAPON_RUNOVERBYCAR);
                            }
                        }
                    }

                    if (entity->m_nStatus == STATUS_SIMPLE) {
                        entity->m_nStatus = STATUS_PHYSICS;
                        if (entity->m_nType == ENTITY_TYPE_VEHICLE) {
                            CCarCtrl::SwitchVehicleToRealPhysics(entityVehicle);
                        }
                    }
                    if (CWorld::bSecondShift) {
                        bResult = true;
                    } else if (totalColPointsToProcess > totalAcceptableColPoints) {
                        return true;
                    }
                }
            }
        }
    } while (scanListIndex);
    return bResult;
}

// 0x54CFF0
bool CPhysical::ProcessCollisionSectorList_SimpleCar(CRepeatSector* repeatSector)
{
    static CColPoint colPoints[32];
    float fThisDamageIntensity = -1.0f;
    float fEntityDamageIntensity = -1.0f;

    if (!m_bUsesCollision)
    {
        return false;
    }
  
    CVector vecBoundingCentre;
    GetBoundCentre(&vecBoundingCentre);

    float fBoundingRadius = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundRadius();
    CPtrListDoubleLink* doubleLinkList = nullptr;

    int32 scanListIndex = 2;
    while (true) {
        switch (--scanListIndex) {
        case 0:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_VEHICLES];
            break;
        case 1:
            doubleLinkList = &repeatSector->m_lists[eRepeatSectorList::REPEATSECTOR_OBJECTS];
            break;
        }

        if (doubleLinkList->GetNode()) {
            break;
        }

        if (!scanListIndex) {
            return false;
        }
    }

    CEntity* entity = nullptr;
    CPhysical* physicalEntity = nullptr;

    int32 totalColPointsToProcess = 0;

    CPtrNodeDoubleLink* node = doubleLinkList->GetNode();
    while (node)
    {
        entity = reinterpret_cast<CEntity*>(node->pItem);
        physicalEntity = static_cast<CPhysical*>(entity);
        node = node->pNext;

        bool isLampTouchingGround = false;
        if (entity->IsObject() && entity->AsObject()->IsFallenLampPost())
            isLampTouchingGround = true;

        if (entity != this
            && !isLampTouchingGround
            && entity->m_nScanCode != CWorld::ms_nCurrentScanCode)
        {
            if (entity->m_bUsesCollision && entity->GetIsTouching(vecBoundingCentre, fBoundingRadius)) {
                entity->m_nScanCode = CWorld::ms_nCurrentScanCode;
                totalColPointsToProcess = ProcessEntityCollision(physicalEntity, &colPoints[0]);
                if (totalColPointsToProcess > 0) {
                    break;
                }
            }
        }
    }

    if (!node)
    {
        if (!scanListIndex)
        {
            return false;
        }
    }

    if (m_bHasContacted && entity->m_bHasContacted)
    {
        if (totalColPointsToProcess > 0)
        {
            for( int32 colPointIndex = 0; colPointIndex < totalColPointsToProcess; colPointIndex++)
            {
                CColPoint* colPoint = &colPoints[colPointIndex];
                if (ApplyCollision(entity, *colPoint, fThisDamageIntensity, fEntityDamageIntensity))
                {
                    SetDamagedPieceRecord(fThisDamageIntensity, entity, *colPoint, 1.0f);
                    physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint, -1.0f);
                }
            }
        }
    }
    else if (m_bHasContacted)
    {
        CVector vecOldFrictionMoveSpeed = m_vecFrictionMoveSpeed;
        CVector vecOldFrictionTurnSpeed = m_vecFrictionTurnSpeed;
        ResetFrictionTurnSpeed();
        ResetFrictionMoveSpeed();
        m_bHasContacted = false;

        if (totalColPointsToProcess > 0)
        {
            for (int32 colPointIndex = 0; colPointIndex < totalColPointsToProcess; colPointIndex++)
            {
                CColPoint* colPoint = &colPoints[colPointIndex];
                if (ApplyCollision(entity, *colPoint, fThisDamageIntensity, fEntityDamageIntensity))
                {
                    SetDamagedPieceRecord(fThisDamageIntensity, entity, *colPoint, 1.0f);
                    physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint, -1.0f);
                    float fSurfaceFriction = g_surfaceInfos->GetAdhesiveLimit(colPoint);
                    float fFriction = fSurfaceFriction / totalColPointsToProcess;
                    if (ApplyFriction(physicalEntity, fFriction, *colPoint))
                    {
                        m_bHasContacted = true;
                        entity->m_bHasContacted = true;
                    }
                }
            } 
        }

        if (!m_bHasContacted)
        {
            m_vecFrictionMoveSpeed = vecOldFrictionMoveSpeed;
            m_vecFrictionTurnSpeed = vecOldFrictionTurnSpeed;
            m_bHasContacted = true;
        }
    }
    else
    {
        if (entity->m_bHasContacted)
        {
            CVector vecOldFrictionMoveSpeed = physicalEntity->m_vecFrictionMoveSpeed;
            CVector vecOldFrictionTurnSpeed = physicalEntity->m_vecFrictionTurnSpeed;
            physicalEntity->ResetFrictionTurnSpeed();
            physicalEntity->ResetFrictionMoveSpeed();
            entity->m_bHasContacted = false;

            if (totalColPointsToProcess > 0)
            {
                for (int32 colPointIndex = 0; colPointIndex < totalColPointsToProcess; colPointIndex++)
                {
                    CColPoint* colPoint = &colPoints[colPointIndex];
                    if (ApplyCollision(entity, *colPoint, fThisDamageIntensity, fEntityDamageIntensity))
                    {
                        SetDamagedPieceRecord(fThisDamageIntensity, entity, *colPoint, 1.0f);
                        physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint, -1.0f);
                        float fSurfaceFriction = g_surfaceInfos->GetAdhesiveLimit(colPoint);
                        float fFriction = fSurfaceFriction / totalColPointsToProcess;
                        if (ApplyFriction(physicalEntity, fFriction, *colPoint))
                        {
                            m_bHasContacted = true;
                            entity->m_bHasContacted = true;
                        }
                    }
                }
            }
            if (!entity->m_bHasContacted)
            {
                physicalEntity->m_vecFrictionMoveSpeed = vecOldFrictionMoveSpeed;
                physicalEntity->m_vecFrictionTurnSpeed = vecOldFrictionTurnSpeed;
                entity->m_bHasContacted = true;
            }
        }
        else if (totalColPointsToProcess > 0)
        {
            for (int32 colPointIndex = 0; colPointIndex < totalColPointsToProcess; colPointIndex++)
            {
                CColPoint* colPoint = &colPoints[colPointIndex];
                if (ApplyCollision(entity, *colPoint, fThisDamageIntensity, fEntityDamageIntensity))
                {
                    SetDamagedPieceRecord(fThisDamageIntensity, entity, *colPoint, 1.0f);
                    physicalEntity->SetDamagedPieceRecord(fEntityDamageIntensity, this, *colPoint, -1.0f);
                    float fSurfaceFriction = g_surfaceInfos->GetAdhesiveLimit(colPoint);
                    float fFriction = fSurfaceFriction / totalColPointsToProcess;
                    if (ApplyFriction(physicalEntity, fFriction, *colPoint))
                    {
                        m_bHasContacted = true;
                        entity->m_bHasContacted = true;
                    }
                }
            }
        }
    }
  
    if (entity->m_nStatus == STATUS_SIMPLE)
    {
        entity->m_nStatus = STATUS_PHYSICS;
        if (entity->m_nType == ENTITY_TYPE_VEHICLE)
        {
            CCarCtrl::SwitchVehicleToRealPhysics(static_cast<CVehicle*>(entity));
        }
    }
    return true; 
}

// 0x54D570
void CPhysical::AttachEntityToEntity(CPhysical* entityAttachTo, CVector vecAttachOffset, CVector vecAttachRotation)
{
    if (!entityAttachTo)
        return;

    CEntity* oldEntityAttachedTo = m_pAttachedTo;
    m_pAttachedTo = entityAttachTo;
    m_pAttachedTo->RegisterReference(reinterpret_cast<CEntity**>(&m_pAttachedTo));
    m_vecAttachOffset = vecAttachOffset;
    if (physicalFlags.bInfiniteMass) 
        m_vecAttachedEntityRotation = GetPosition();
    else 
        m_vecAttachedEntityRotation = vecAttachRotation;
    m_qAttachedEntityRotation.real = 0.0f;
    m_qAttachedEntityRotation.imag = CVector(0.0f, 0.0f, 0.0f);
    m_pEntityIgnoredCollision = oldEntityAttachedTo;
    if (physicalFlags.bDisableCollisionForce) {
        physicalFlags.bCollidable = false;
        PositionAttachedEntity();
    }
    else {
        if (m_pAttachedTo->m_nType > ENTITY_TYPE_BUILDING && m_pAttachedTo->m_nType < ENTITY_TYPE_DUMMY
            && m_pAttachedTo->physicalFlags.bDisableCollisionForce 
            && m_nType == ENTITY_TYPE_OBJECT && !physicalFlags.bInfiniteMass) 
        {
            physicalFlags.bDisableCollisionForce = true;
            m_fMass = 99999.9f;
            m_fTurnMass = 99999.9f;
        }
        PositionAttachedEntity();
    }
}

// 0x54D690
void CPhysical::AttachEntityToEntity(CPhysical* entityAttachTo, CVector* vecAttachOffset, CQuaternion* attachRotation)
{
    if (!entityAttachTo)
        return;

    CPhysical* oldEntityAttachedTo = m_pAttachedTo;
    m_pAttachedTo = entityAttachTo;
    m_pAttachedTo->RegisterReference(reinterpret_cast<CEntity**>(&m_pAttachedTo));
    CMatrix entityAttachedtoMatrix(m_pAttachedTo->GetMatrix());
    CAutomobile* attachedToAutoMobile = static_cast<CAutomobile*>(m_pAttachedTo);
    if (m_nType == ENTITY_TYPE_OBJECT && m_pAttachedTo->m_nModelIndex == MODEL_FORKLIFT) {
        RwFrame* pCarMiscAFrame = attachedToAutoMobile->m_aCarNodes[CAR_MISC_A];
        if (pCarMiscAFrame) 
            entityAttachedtoMatrix.UpdateMatrix(RwFrameGetLTM(pCarMiscAFrame));
    }

    if (vecAttachOffset) {
        m_vecAttachOffset = *vecAttachOffset;
    }
    else {
        CVector distance = GetPosition() - entityAttachedtoMatrix.GetPosition();
        m_vecAttachOffset.x = DotProduct(&entityAttachedtoMatrix.GetRight(), &distance);
        m_vecAttachOffset.y = DotProduct(&entityAttachedtoMatrix.GetForward(), &distance);
        m_vecAttachOffset.z = DotProduct(&entityAttachedtoMatrix.GetUp(), &distance);
    }

    if (attachRotation) {
        m_qAttachedEntityRotation = *attachRotation;
    }
    else {
        CMatrix entityAttachedToMatrixInverted;
        Invert(entityAttachedtoMatrix, entityAttachedToMatrixInverted);
        entityAttachedToMatrixInverted *= *m_matrix;
        RwMatrixTag rwMatrix;
        entityAttachedToMatrixInverted.CopyToRwMatrix(&rwMatrix);
        RtQuatConvertFromMatrix((RtQuat*)&m_qAttachedEntityRotation, &rwMatrix);
    }

    if (physicalFlags.bDisableCollisionForce) {
        physicalFlags.bCollidable = false;
    }
    else {
        if (m_pAttachedTo->m_nType > ENTITY_TYPE_BUILDING && m_pAttachedTo->m_nType < ENTITY_TYPE_DUMMY
            && m_pAttachedTo->physicalFlags.bDisableCollisionForce
            && m_nType == ENTITY_TYPE_OBJECT && !physicalFlags.bInfiniteMass) 
        {
            physicalFlags.bDisableCollisionForce = true;
            m_fMass = 99999.9f;
            m_fTurnMass = 99999.9f;
        }
    }

    if (physicalFlags.bInfiniteMass)
        m_vecAttachedEntityRotation = GetPosition();

    m_pEntityIgnoredCollision = oldEntityAttachedTo;
    PositionAttachedEntity();
}

// 0x54D920
bool CPhysical::CheckCollision()
{
    m_bCollisionProcessed = false;
    if (m_nType == ENTITY_TYPE_PED)
    {
        CPed* ped = static_cast<CPed*>(this);
        if (!m_pAttachedTo && !physicalFlags.b17 && !physicalFlags.bProcessingShift && !physicalFlags.b13) {
            ped->m_standingOnEntity = nullptr;
            if (ped->bIsStanding) {
                ped->bIsStanding = false;
                ped->bWasStanding = true;
            }
        }

        if (ped->IsPlayer()) {
            CTaskSimpleClimb* pTaskClimb = ped->m_pIntelligence->GetTaskClimb();
            if (pTaskClimb) {
                char nHeightForPos = pTaskClimb->m_nHeightForPos;
                if (nHeightForPos == CLIMB_GRAB || nHeightForPos == CLIMB_PULLUP 
                    || nHeightForPos == CLIMB_STANDUP || nHeightForPos == CLIMB_VAULT) {
                    physicalFlags.b13 = true;
                }
            }
        }
    }

    CWorld::IncrementCurrentScanCode();

    CRect boundRect;
    GetBoundRect(&boundRect);
    int32 startSectorX = CWorld::GetSectorX(boundRect.left);
    int32 startSectorY = CWorld::GetSectorY(boundRect.top);
    int32 endSectorX = CWorld::GetSectorX(boundRect.right);
    int32 endSectorY = CWorld::GetSectorY(boundRect.bottom);
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            if (ProcessCollisionSectorList(sectorX, sectorY))
                return true;
        }
    }
    return false;  
}

// 0x54DAB0
bool CPhysical::CheckCollision_SimpleCar()
{
    m_bCollisionProcessed = false;
    CWorld::IncrementCurrentScanCode();
    CEntryInfoNode* entryInfoNode = m_pCollisionList.m_pNode;
    if (!entryInfoNode)
        return false;

    while (!ProcessCollisionSectorList_SimpleCar(entryInfoNode->m_pRepeatSector))
    {
        entryInfoNode = entryInfoNode->m_pNext;
        if (!entryInfoNode)
            return false;
    }
    return true;
}
