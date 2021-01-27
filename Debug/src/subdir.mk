################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/EntityManager.cpp \
../src/Game.cpp \
../src/MainMenu.cpp \
../src/Map.cpp \
../src/Player.cpp \
../src/TextureManager.cpp \
../src/main.cpp 

OBJS += \
./src/Camera.o \
./src/EntityManager.o \
./src/Game.o \
./src/MainMenu.o \
./src/Map.o \
./src/Player.o \
./src/TextureManager.o \
./src/main.o 

CPP_DEPS += \
./src/Camera.d \
./src/EntityManager.d \
./src/Game.d \
./src/MainMenu.d \
./src/Map.d \
./src/Player.d \
./src/TextureManager.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


