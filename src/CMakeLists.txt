cmake_minimum_required (VERSION 3.19)

add_library(FamiliarEngineLib INTERFACE)
target_include_directories(FamiliarEngineLib INTERFACE FamiliarEngine )

add_executable(Familiar 
	"FamiliarGame/main.cpp"
	 "FamiliarGame/StarSystemContext/OrbitablesManager.hpp")


target_link_libraries(Familiar
  PRIVATE
	${CONAN_LIBS}
	FamiliarEngineLib
  )
