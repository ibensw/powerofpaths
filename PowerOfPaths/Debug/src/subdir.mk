################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Main.cpp \
../src/configuration.cpp \
../src/nodes.cpp \
../src/servernode.cpp 

OBJS += \
./src/Main.o \
./src/configuration.o \
./src/nodes.o \
./src/servernode.o 

CPP_DEPS += \
./src/Main.d \
./src/configuration.d \
./src/nodes.d \
./src/servernode.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -g3 -p -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


