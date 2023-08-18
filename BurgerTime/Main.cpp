#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Bun.h"
#include "Minigin.h"
#include "CollisionComponent.h"
#include "FPS.h"
#include "Game.h"

int main(int, char* []) {
	Game burgerTime{};
	burgerTime.Run();
	return 0;
}