

#include <Program.h>
#include <stdio.h>
#undef main

int main(int argc, char* argv[]) {
	return hugGameEngine::App::GetInstance()->Execute(argc, argv);
}