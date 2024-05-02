
#include "../Engine/Engine.h"
#include "States.h"
#include "Fonts.h"
#include "Main_menu.h"

Main_menu::Main_menu()
{
}

void Main_menu::Load()
{
	current_button = 0;
	title = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture("CS230 Engine Test", ColorToInt({ 167, 138, 255, 255 }));

	strings[Side_Scroller] = "Side Scroller";
	strings[Space_Shooter] = "Space Shooter";
	strings[Exit] = "Exit";

	buttons[Side_Scroller] = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(strings[Side_Scroller], ColorToInt(WHITE));
	buttons[Space_Shooter] = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(strings[Space_Shooter], ColorToInt({ 134, 179, 0, 255 }));
	buttons[Exit] = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(strings[Exit], ColorToInt({ 134, 179, 0, 255 }));
}

void Main_menu::Update([[maybe_unused]] double dt) {
	int before_button = current_button;
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Down) && current_button < Size - 1){
		++current_button;
	}else if(Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Up) && current_button > 0){
		--current_button;
	}

	if (current_button != before_button) {
		buttons[before_button] = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(strings[before_button], ColorToInt({ 134, 179, 0, 255 }));
		buttons[current_button] = Engine::GetFont(static_cast<int>(Fonts::Outlined)).PrintToTexture(strings[current_button], ColorToInt(WHITE));
	}

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Enter)) {
		switch (current_button) {
		case Side_Scroller:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode1));
			break;
		case Space_Shooter:
			Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Mode2));
			break;
		case Exit:
			Engine::GetGameStateManager().ClearNextGameState();
			break;
		}
	}
}

void Main_menu::Unload() {
}

void Main_menu::Draw() {
	Engine::GetWindow().Clear(ColorToInt({33, 32, 36, 255}));
	int x = Engine::GetWindow().GetSize().x;
	int y = Engine::GetWindow().GetSize().y - title->GetSize().y;
	title->Draw(Math::TranslationMatrix(Math::ivec2{ (x - title->GetSize().x)/2, y - 40 }));
	for (int i = Side_Scroller, gap = y / 2 - 30; i <= Exit; ++i, gap += 100) {
		buttons[i]->Draw(Math::TranslationMatrix(Math::ivec2{ (x - buttons[i]->GetSize().x) / 2, y - gap }));
	}
}