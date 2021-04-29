// Singleton that keeps track of time related items
class Time {
public:
	static float getDeltaTime();
	static void updateDeltaTime();
private:
	Time();
	static float lastFrame;
	static float deltaTime;
};