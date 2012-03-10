################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/simulator/schedule.cpp \
../src/simulator/simulator.cpp 

OBJS += \
./src/simulator/schedule.o \
./src/simulator/simulator.o 

CPP_DEPS += \
./src/simulator/schedule.d \
./src/simulator/simulator.d 


# Each subdirectory must supply rules for building sources it contributes
src/simulator/%.o: ../src/simulator/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -g3 -p -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


