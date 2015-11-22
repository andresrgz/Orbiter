################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Entities/Asteroid.cpp \
../src/Entities/Entity.cpp \
../src/Entities/Planet.cpp \
../src/Entities/Player.cpp 

OBJS += \
./src/Entities/Asteroid.o \
./src/Entities/Entity.o \
./src/Entities/Planet.o \
./src/Entities/Player.o 

CPP_DEPS += \
./src/Entities/Asteroid.d \
./src/Entities/Entity.d \
./src/Entities/Planet.d \
./src/Entities/Player.d 


# Each subdirectory must supply rules for building sources it contributes
src/Entities/%.o: ../src/Entities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


