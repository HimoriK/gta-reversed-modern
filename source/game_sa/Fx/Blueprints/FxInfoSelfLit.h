#pragma once

#include "FxInfo.h"
#include "FxInterpInfoU255.h"

class FxInfoSelfLit_c : public FxInfo_c {
protected:
    FxInterpInfoU255_c m_InterpInfo;

public:
    FxInfoSelfLit_c();
    ~FxInfoSelfLit_c() override = default; // 0x4A79D0

    void Load(FILESTREAM file, int32 version) override;
    void GetValue(float currentTime, float mult, float totalTime, float length, bool useConst, void* info) override;
};
