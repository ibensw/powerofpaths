################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ring/job.cpp \
../src/ring/node.cpp \
../src/ring/ring.cpp 

OBJS += \
./src/ring/job.o \
./src/ring/node.o \
./src/ring/ring.o 

CPP_DEPS += \
./src/ring/job.d \
./src/ring/node.d \
./src/ring/ring.d 


# Each subdirectory must supply rules for building sources it contributes
src/ring/%.o: ../src/ring/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -g3 -p -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


