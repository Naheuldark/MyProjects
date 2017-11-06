#ifndef GERSTNERWAVEMODEL_HPP
#define GERSTNERWAVEMODEL_HPP

#include <iostream>
#include <assert.h>
#include "Height.h"
#include "Dvector.h"
#include "WaveModel.h"
#include "GerstnerWave.h"

class GerstnerWaveModel :
    public WaveModel
{
    public:
        ~GerstnerWaveModel();
        GerstnerWaveModel(); 

    private:
        Dvector ki, Ai, wi, phii;
};

#endif
