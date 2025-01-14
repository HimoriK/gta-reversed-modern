#pragma once

#include "FxInfo.h"
#include "FxInterpInfo32.h"

class FxInfoJitter_c : public FxInfo_c {
protected:
    FxInterpInfo32_c m_InterpInfo;

public:
    FxInfoJitter_c();
    ~FxInfoJitter_c() override = default;

    void Load(FILESTREAM file, int32 version) override;
    void GetValue(float currentTime, float mult, float totalTime, float length, bool useConst, void* info) override;
};
