#pragma once

#include "FxInfo.h"
#include "FxInterpInfo32.h"

class FxInfoFriction_c : public FxInfo_c {
protected:
    FxInterpInfo32_c m_InterpInfo;

public:
    FxInfoFriction_c();
    ~FxInfoFriction_c() override = default; // 0x4A6F60

    void Load(FILESTREAM file, int32 version) override;
    void GetValue(float currentTime, float mult, float totalTime, float length, bool useConst, void* info) override;
};
