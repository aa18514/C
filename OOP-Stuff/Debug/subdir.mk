################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../circles.cpp \
../main.cpp \
../points.cpp \
../shapes.cpp \
../triangle.cpp 

OBJS += \
./circles.o \
./main.o \
./points.o \
./shapes.o \
./triangle.o 

CPP_DEPS += \
./circles.d \
./main.d \
./points.d \
./shapes.d \
./triangle.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


