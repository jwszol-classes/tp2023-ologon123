#include "AppEngine.h"
#include "SquareBlock.h"
#include "TriangleBlock.h"
#include "CircleBlock.h"

using namespace std;
using namespace Gdiplus;

AppEngine::AppEngine()
{
	srand(time(NULL));
	GdiplusStartup(&gdiplusToken, &gdiplusParameters, NULL);
	blocksCreators.insert(pair<string, function<Block * (int, int)>>("Square", [](int x, int y) { return new SquareBlock(x, y, 75); }));
	blocksCreators.insert(pair<string, function<Block * (int, int)>>("Circle", [](int x, int y) { return new CircleBlock(x, y, 50); }));
	blocksCreators.insert(pair<string, function<Block * (int, int)>>("Triangle", [](int x, int y) { return new TriangleBlock(x, y, 25); }));
	simulator = shared_ptr<Simulator>(new Simulator({"Triangle", "Square", "Circle" }));
	initializeApp();
	drawer = shared_ptr<Drawer>(new Drawer());
}

AppEngine::~AppEngine()
{
	drawer = nullptr;
	messenger = nullptr;
	GdiplusShutdown(gdiplusToken);
}

void AppEngine::start(HINSTANCE hInstance, int nCmdShow)
{
	createWindow(hInstance, nCmdShow);
	eventsLoop();
}

void AppEngine::eventsLoop()
{
	MSG communicate;
	while (GetMessage(&communicate, NULL, 0, 0))
	{
		TranslateMessage(&communicate);
		DispatchMessage(&communicate);
	}
}

LRESULT CALLBACK eventsHandle(HWND window, UINT messageCode, WPARAM wParam, LPARAM lParam)
{
	AppEngine* appEngine = (AppEngine*)GetWindowLongPtr(window, GWLP_USERDATA);
	switch (messageCode)
	{
	case WM_COMMAND:
		if (((HWND)lParam) && (HIWORD(wParam) == BN_CLICKED))
		{
			appEngine->buttonsManager->handleButtonOption(LOWORD(wParam));
			appEngine->createPaintMessage();
		}
		return 0;
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		appEngine->executePaint();
		return 0;
	default:
		return DefWindowProc(window, messageCode, wParam, lParam);
	}
}

void AppEngine::executePaint()
{
	HDC context;
	PAINTSTRUCT paint;
	context = BeginPaint(*window, &paint);
	drawer->sendContext(context);
	drawer->drawTowers(towers);
	drawer->drawCrane(crane);
	messenger->drawMessages(context);
	EndPaint(*window, &paint);
}

void AppEngine::createPaintMessage()
{
	InvalidateRect(*window, NULL, true);
}

void AppEngine::createWindow(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS our_class; //zdefiniowanie klasy okna
	LPCWSTR class_name = L"CraneSimulator"; // szerokie litery - klasy
	LPCWSTR menu_name = L"CraneSimulator";  // szerokie litery - menu

	our_class.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; //szerokoœæ, wysokoœæ, x2 klikniêcie myszk¹
	our_class.lpfnWndProc = eventsHandle;
	our_class.cbClsExtra = 0; // brak dodatkowej pamiêci
	our_class.cbWndExtra = 0; // brak dodatkowej pamiêci
	our_class.hInstance = hInstance;
	our_class.hIcon = 0; // ikonka domyœl. ustawiony na 0
	our_class.hCursor = LoadCursor(0, IDC_ARROW); // kursor domyœl. ustawiony na 0
	our_class.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH); //jasnoszaret³o
	our_class.lpszMenuName = menu_name; 
	our_class.lpszClassName = class_name; // nazwa klasy okna
	LPCWSTR title = L"CraneSimulator.exe";
	RegisterClass(&our_class); // zachowanie i wygl¹d klasy okna
	auto createdWindow = CreateWindow(class_name, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		150, 0, 1200, 800, NULL, NULL, hInstance, NULL); // standardowe cechy okna/okno widoczne od razu po utworzeniu/ekran w poziomie/w pionie/ szerokoœæ px
	// wysokoœæ px/ brak menu/brak okna nadrzêdnego//..// argument do przekazywania danych u¿ytkownika do okna
	SetWindowLongPtr(createdWindow, GWLP_USERDATA, (LONG_PTR)this);
	window = std::make_shared<HWND>(std::move(createdWindow));// wsóldzielony wskaznik do uchwytu okna 
	buttonsManager->createButtons(window);
	ShowWindow(*window, nCmdShow);//wywo³uje wyœwietlenie okna na ekranie
	UpdateWindow(*window);//aktualizowanie okna
}

void AppEngine::initializeTowers()
{
	vector<string> blocksTypes{"Square", "Triangle", "Circle"};
	int numberOfBlocksTypes = blocksTypes.size();
	int initX = Crane::BASIS_MIN_X + Crane::WIDTH + Block::WIDTH / 2;//pozycja w osi x / min. pozycja - podstawa dŸwigu/../wycentrowanie w po³owie bloczku
	int towerX = initX + Block::WIDTH;
	int numberOfTowers = Crane::ARM_LENGTH / Block::WIDTH;
	int randomNumber = rand() % 50;//uzywana w blockstypes
	for (int i = 0; i < numberOfTowers - 2; i++) 
	{
		int numberOfElements = rand() % 3 + 1;
		string blockType = blocksTypes[(randomNumber + i) % numberOfBlocksTypes];
		towers->push_back(shared_ptr<Tower>(new Tower(blocksCreators[blockType], numberOfElements, towerX, Crane::BASIS - Block::HEIGHT / 2)));
		towerX += Block::WIDTH;
	}
	towers->push_back(shared_ptr<Tower>(new Tower(blocksCreators["Square"], 0, towerX, Crane::BASIS - Block::HEIGHT / 2)));
	towers->insert(towers->begin(), shared_ptr<Tower>(shared_ptr<Tower>(new Tower(blocksCreators["Square"], 0, initX, Crane::BASIS - Block::HEIGHT / 2))));
}

void AppEngine::initializeApp()
{
	towers = shared_ptr<vector<shared_ptr<Tower>>>(new vector<shared_ptr<Tower>>);
	initializeTowers();
	shared_ptr<HookController> hookController = shared_ptr<HookController>(new HookController(towers));
	crane = shared_ptr<Crane>(new Crane(hookController, INITIAL_WEIGHT));
	auto refreshGui = [this]() {
		this->createPaintMessage();
		this->executePaint();
	};
	auto restartWorld = [this]() { this->initializeApp(); };
	shared_ptr<SimulatorService> simulatorService(new SimulatorService(towers, crane, restartWorld, refreshGui));
	simulator->setService(simulatorService);
	errorsMessages = shared_ptr<vector<string>>(new vector<string>());
	messenger = shared_ptr<Messenger>(new Messenger(crane, errorsMessages));
	buttonsManager = shared_ptr<ButtonsManager>(new ButtonsManager(crane, simulator, errorsMessages));
}