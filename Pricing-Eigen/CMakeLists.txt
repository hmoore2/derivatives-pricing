project(Pricing-Eigen)

set(HEADER_FILES
        MathsLib.h
        BlackScholesModel.h
        RandomBase.h

)

set(SOURCE_FILES
        MathsLib.cpp
        BlackScholesModel.cpp
        ContinuousTimeOption.cpp
        ContinuousTimeOptionBase.cpp
        MonteCarloPricer.cpp
        MonteCarloPricer.h
        CallOption.cpp
        PathIndependentOption.cpp
        PutOption.cpp
        DigitalOption.cpp
        AsianOption.cpp
        KnockoutOption.cpp
        UpAndOutOption.cpp
        DownAndOutOption.cpp
        DownAndOutOption.h
        UpAndInOption.cpp
        LookbackOption.cpp
        LookbackOption.h
        EquityModel.h
        EquityModel.cpp
        AmericanCallOption.h
        EarlyExerciseOption.h
        EarlyExerciseOptionBase.cpp
        EarlyExerciseOptionBase.h
        AmericanCallOption.cpp
        RandomBase.cpp
)

add_library(Pricing-Eigen STATIC ${SOURCE_FILES} ${HEADER_FILES})