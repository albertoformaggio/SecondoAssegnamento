class Platform
{
public:
	bool isEmpty();
	void reserve();
	void free();

private:
	bool reserved_;
};