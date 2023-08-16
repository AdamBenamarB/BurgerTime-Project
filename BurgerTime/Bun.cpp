#include "Bun.h"

#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "IngredientComponent.h"
#include "Input.h"
#include "Scene.h"
#include "Tags.h"

dae::Bun::Bun(dae::Scene& scene, Vec2 loc)
{
	Initialize(scene, loc);
}

void dae::Bun::Initialize(dae::Scene& scene, Vec2 loc)
{
	std::vector<RenderComponent*> sprites;
	std::vector<CollisionComponent*> cols;
	auto go = std::make_shared<dae::GameObject>();

	//SPRITES
	auto rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\bun0.png");
	rc->SetDimensions(16, 16);

	sprites.push_back(rc);

	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\bun1.png");
	rc->SetDimensions(16, 16);
	rc->SetOffsetX(16);

	sprites.push_back(rc);

	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\bun2.png");
	rc->SetDimensions(16, 16);
	rc->SetOffsetX(32);

	sprites.push_back(rc);

	rc = go->AddComponent<dae::RenderComponent>();
	rc->SetTexture("\\Sprites\\Ingredients\\bun3.png");
	rc->SetDimensions(16, 16);
	rc->SetOffsetX(48);

	sprites.push_back(rc);

	//COLLISION
	auto col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);

	cols.push_back(col);

	col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);
	col->SetOffset(16, 0);

	cols.push_back(col);

	col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);
	col->SetOffset(32, 0);

	cols.push_back(col);

	col = go->AddComponent<CollisionComponent>();
	col->SetSize(16, 14);
	col->SetOffset(48, 0);

	cols.push_back(col);

	auto ingredient = go->AddComponent<IngredientComponent>();
	ingredient->SetCollisions(cols);
	ingredient->SetSprites(sprites);

	go->GetTransform()->SetLocalPosition(loc.x, loc.y + 22, 0);
	go->SetTag(Tag::bun);
	scene.Add(go);

}
