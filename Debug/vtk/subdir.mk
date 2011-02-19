################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../vtk/TriangulateTerrainMap.cxx 

OBJS += \
./vtk/TriangulateTerrainMap.o 

CXX_DEPS += \
./vtk/TriangulateTerrainMap.d 


# Each subdirectory must supply rules for building sources it contributes
vtk/%.o: ../vtk/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


