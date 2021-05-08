// Singleton that keeps track of time related items
class Time {
public:
	static void start();
	static float getDeltaTime();
	static void updateDeltaTime();
	static int getFrames();
private:
	static const int FPS = 24;

	Time();
	static float lastFrame;
	static float deltaTime;
	static float startTime;
};