#include "allClasses.h"

using namespace std;

// *************** Animal ************* //
#pragma region Animal
Animal::Animal() : m_childCount(0), m_avgLifetime(0), m_color(NULL) {
	m_color = new char[5];
	strcpy(m_color, "GRAY");
};
Animal::Animal(const char* color, int childs, float avgLifetime) {
	m_color = new char[strlen(color) + 1];
	strcpy(m_color, color);
	m_childCount = childs;
	m_avgLifetime = avgLifetime;
};
Animal::Animal(ifstream& in_file) : m_childCount(0), m_avgLifetime(0), m_color(NULL) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_color = new char[len + 1];
	in_file.read(m_color, len);
	m_color[len] = '\0';
	in_file.read((char*)&m_childCount, sizeof(m_childCount));
	in_file.read((char*)&m_avgLifetime, sizeof(m_avgLifetime));
};

Animal::~Animal() {
	if(m_color)
		delete m_color;
};


Animal* Animal::clone() {
	return new Animal(m_color, m_childCount, m_avgLifetime);
};


const char* Animal::GetColor() const {
	return m_color;
};//return the color of the animal
int			Animal::GetChildCount() const {
	return m_childCount;
};//return the child count of the animal
float		Animal::GetLifetime() const {
	return m_avgLifetime;
};//return the life time of the animal
#pragma endregion 

// *************** Mammals ************* //
#pragma region Mammals
Mammals::Mammals() {
	m_pregnancyTime = 0;
	m_milkLiters = 0;
};//set the default color to GRAY and other params to 0
Mammals::Mammals(const char* color, int childs, float avgLifetime, float preg, float milk) : Animal(color, childs, avgLifetime) {
	m_pregnancyTime = preg;
	m_milkLiters = milk;
};//init the Mammals with a given attributes
Mammals::Mammals(ifstream& in_file) : Animal::Animal(in_file) {
	in_file.read((char*)&m_pregnancyTime, sizeof(m_pregnancyTime));
	in_file.read((char*)&m_milkLiters, sizeof(m_milkLiters));
};//init the Mammals from a binary file

Mammals::~Mammals() {};

Animal* Mammals::clone() {
	return new Mammals(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters);
};

float		Mammals::GetPregnanceTime() const {
	return m_pregnancyTime;
};//return the pregnance time of the animal
float		Mammals::GetMilk() const {
	return m_milkLiters;
};//return the milk liters of the animal

#pragma endregion 

// *************** Birds ************* //
#pragma region Birds
Birds::Birds() {
	m_incubationTime = 0;
};//set the default color to GRAY and other params to 0
Birds::Birds(const char* color, int childs, float avgLifetime, float incubation) : Animal(color, childs, avgLifetime) {
	m_incubationTime = incubation;
};//init the Birds with a given attributes
Birds::Birds(ifstream& in_file) : Animal(in_file) {
	in_file.read((char*)&m_incubationTime, sizeof(m_incubationTime));
};//init the Birds from a binary file

Birds::~Birds() {};

Animal* Birds::clone() {
	return new Birds(m_color, m_childCount, m_avgLifetime, m_incubationTime);
};

float Birds::GetIncubationTime() const {
	return m_incubationTime;
};//return the incubation time of the animal
#pragma endregion 

// *************** Fish ************* //
#pragma region Fish
Fish::Fish() {
	m_finCount = 0;
	m_gillsCount = 0;
};//set the default color to GRAY and other params to 0
Fish::Fish(const char* color, int childs, float avgLifetime, int fin, int gills) : Animal(color, childs, avgLifetime) {
	m_finCount = fin;
	m_gillsCount = gills;
};//init the Fish with a given attributes
Fish::Fish(ifstream& in_file) : Animal(in_file) {
	in_file.read((char*)&m_finCount, sizeof(m_finCount));
	in_file.read((char*)&m_gillsCount, sizeof(m_gillsCount));
};//init the Fish from a binary file
Fish::~Fish() {};

Animal* Fish::clone() {
	return new Fish(m_color, m_childCount, m_avgLifetime, m_finCount, m_gillsCount);
};

int	Fish::GetFinCount() const {
	return m_finCount;
};//return the fin count of the animal
int	Fish::GetGillsCount() const {
	return m_gillsCount;
};//return the gills count of the animal
#pragma endregion

// *************** Horse ************* //
#pragma region Horse

Horse::Horse() : m_type(NULL) {};//set the default color to GRAY and other params to 0
Horse::Horse(const char* color, int childs, float avgLifetime, float preg, float milk, const char* type) : Mammals(color, childs, avgLifetime, preg, milk) {
	m_type = new char[strlen(type) + 1];
	strcpy(m_type, type);
};//init the Horse with a given attributes
Horse::Horse(ifstream& in_file) : Mammals(in_file) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_type = new char[len + 1];
	in_file.read(m_type, len);
	m_type[len] = '\0';
};//init the Horse from a binary file
Horse::~Horse() { delete m_type; };

Animal* Horse::clone() {
	return new Horse(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_type);
};

const char* Horse::GetType() const { return m_type; };//return the type of the horse

#pragma endregion

// *************** Flamingo ************* //
#pragma region Flamingo
Flamingo::Flamingo() { m_avgHeight = 0; };//set the default color to GRAY and other params to 0
Flamingo::Flamingo(const char* color, int childs, float avgLifetime, float incubation, float avgHeight) : Birds(color, childs, avgLifetime, incubation) {
	m_avgHeight = avgHeight;
};//init the Flamingo with a given attributes
Flamingo::Flamingo(ifstream& in_file) : Birds(in_file) {
	in_file.read((char*)&m_avgHeight, sizeof(m_avgHeight));
};//init the Flamingo from a binary file
Flamingo::~Flamingo() {};

Animal* Flamingo::clone() {
	return new Flamingo(m_color, m_childCount, m_avgLifetime, m_incubationTime, m_avgHeight);
};

float Flamingo::GetHeight() const { return m_avgHeight; };//return the avg height of the flamingo

#pragma endregion


// *************** MammalsFish ************* //
#pragma region MammalsFish
MammalsFish::MammalsFish(): Animal() {};//set the default color to GRAY and other params to 0
MammalsFish::MammalsFish(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills) 
	: Mammals(color, childs, avgLifetime, preg, milk),
	  Fish(color, childs, avgLifetime, fin, gills)
{};//init the MammalsFish with a given attributes
MammalsFish::MammalsFish(ifstream& in_file) : Mammals(in_file), Fish(in_file) {};//init the MammalsFish from a binary file

MammalsFish::~MammalsFish() {};

Animal* MammalsFish::clone() { 
	return new MammalsFish(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_finCount, m_gillsCount); 
};

#pragma endregion

// *************** GoldFish ************* //
#pragma region GoldFish
GoldFish::GoldFish() {
	m_avgWeight = 0;
	m_avgLength = 0;
};//set the default color to GRAY and other params to 0
GoldFish::GoldFish(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills, float avgW, float avgL) : MammalsFish(color, childs, avgLifetime, preg, milk, fin, gills) {
	m_avgWeight = avgW;
	m_avgLength = avgL;
};//init the GoldFish with a given attributes
GoldFish::GoldFish(ifstream& in_file) : MammalsFish(in_file) {
	in_file.read((char*)&m_avgWeight, sizeof(m_avgWeight));
	in_file.read((char*)&m_avgLength, sizeof(m_avgLength));
};//init the GoldFish from a binary file
GoldFish::~GoldFish() {};

Animal* GoldFish::clone() {
	return new GoldFish(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_finCount, m_gillsCount, m_avgWeight, m_avgLength);
};

float GoldFish::GetWeight() const { return m_avgWeight; };//return the avg weight of the gold fish
float GoldFish::GetLength() const { return m_avgLength; };//return the avg length of the gold fish
#pragma endregion


// *************** Mermaid ************* //
#pragma region Mermaid

Mermaid::Mermaid() {
	m_firstName = NULL;
	m_lastName = NULL;
};//set the default color to GRAY and other params to 0
Mermaid::Mermaid(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills, const char* firstName, const char* lastName) : MammalsFish(color, childs, avgLifetime, preg, milk, fin, gills) {
	m_firstName = new char[strlen(firstName) + 1];
	strcpy(m_firstName, firstName);
	m_lastName = new char[strlen(lastName) + 1];
	strcpy(m_lastName, lastName);
};//init the Mermaid with a given attributes
Mermaid::Mermaid(ifstream& in_file) : MammalsFish(in_file) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_firstName = new char[len + 1];
	in_file.read(m_firstName, len);
	m_firstName[len] = '\0';
	in_file.read((char*)&len, sizeof(len));
	m_lastName = new char[len + 1];
	in_file.read(m_lastName, len);
	m_lastName[len] = '\0';

};//init the Mermaid from a binary file
Mermaid::~Mermaid() {
	if(m_firstName)
		delete m_firstName;
	if(m_lastName)
		delete m_lastName;
};

Animal* Mermaid::clone() {
	return new Mermaid(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_finCount, m_gillsCount, m_firstName, m_lastName);
};

const char* Mermaid::GetFirstName() const { return m_firstName; };//return the first name of the mermaid
const char* Mermaid::GetLastName() const { return m_lastName; };//return the last name of the mermaid

#pragma endregion

// *************** Zoo ************* //
#pragma region Zoo
Zoo::Zoo() {
	m_name = NULL;
	m_address = NULL;
	m_ticketPrice = 0;
	m_openHours = NULL;
	m_closeHours = NULL;
	m_numOfAnimals = 0;
	m_animals = NULL;
};//default c'tor  - all to 0 or null
Zoo::Zoo(const char* name, const char* address, float ticket, const char* open, const char* close) {
	m_name = new char[strlen(name)+1];
	strcpy(m_name, name);

	m_address  = new char[strlen(address) + 1];
	strcpy(m_address, address);

	m_ticketPrice = 0;

	m_openHours = new char[strlen(open) + 1];
	strcpy(m_openHours, open);

	m_closeHours = new char[strlen(close) + 1];
	strcpy(m_closeHours, close);

	m_numOfAnimals = 0;
	m_animals = NULL;
};//c'tor with data - init class
Zoo::Zoo(const Zoo& other) {
	m_name = new char[strlen(other.m_name) + 1];
	strcpy(m_name, other.m_name);

	m_address = new char[strlen(other.m_address) + 1];
	strcpy(m_address, other.m_address);

	m_ticketPrice = other.m_ticketPrice;

	m_openHours = new char[strlen(other.m_openHours) + 1];
	strcpy(m_openHours, other.m_openHours);

	m_closeHours = new char[strlen(other.m_closeHours) + 1];
	strcpy(m_closeHours, other.m_closeHours);

	m_numOfAnimals = other.m_numOfAnimals;
	m_animals = other.m_animals;
};//c'tor with data - init class
Zoo::Zoo(ifstream& in_file) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_name = new char[len + 1];
	in_file.read(m_name, len);
	m_name[len] = '\0';

	in_file.read((char*)&len, sizeof(len));
	m_address = new char[len + 1];
	in_file.read(m_address, len);
	m_address[len] = '\0';

	in_file.read((char*)&m_ticketPrice, sizeof(m_ticketPrice));

	in_file.read((char*)&len, sizeof(len));
	m_openHours = new char[len + 1];
	in_file.read(m_openHours, len);
	m_openHours[len] = '\0';

	in_file.read((char*)&len, sizeof(len));
	m_closeHours = new char[len + 1];
	in_file.read(m_closeHours, len);
	m_closeHours[len] = '\0';

	in_file.read((char*)&m_numOfAnimals, sizeof(m_numOfAnimals));
	m_animals = new Animal*[m_numOfAnimals];
	char *type;
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		in_file.read((char*)&len, sizeof(len));
		type = new char[len + 1];
		in_file.read(type, len);
		type[len] = '/0';
		if(strcmp(type, "Horse") == 0)
			m_animals[i] = new Horse(in_file);
		if (strcmp(type, "Flamingo") == 0)
			m_animals[i] = new Flamingo(in_file);
		if (strcmp(type, "GoldFish") == 0)
			m_animals[i] = new Horse(in_file);
		if (strcmp(type, "Mermaid") == 0)
			m_animals[i] = new Horse(in_file);
		delete type;
	}
};//c'tor that gets a binary file and loads the data of the zoo from the file
Zoo::~Zoo() {
	if (m_name)
		delete m_name;
	if (m_address)
		delete m_address;
	if (m_openHours)
		delete m_openHours;
	if (m_closeHours)
		delete m_closeHours;
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		delete m_animals[i];
	}
	if (m_animals)
		delete[] m_animals;
};//d'tor


const char*		Zoo::GetName() const { return m_name; };//return the name of the zoo
const char*		Zoo::GetAddress() const { return m_address; };//return the address of the zoo
float			Zoo::GetTicketPrice() const { return m_ticketPrice; };//return the ticket price of the zoo
const char*		Zoo::GetOpenHour() const { return m_openHours; };//return the open hour of the zoo
const char*		Zoo::GetCloseHour() const { return m_closeHours; };//return the close hour of the zoo
int				Zoo::GetNumOfAnimals() const { return m_numOfAnimals; };//return the num of animals in the zoo
Animal**		Zoo::GetAnimals() const { return m_animals; };//return the animals array of the zoo

void Zoo::AddAnimal(Animal* an) {
	Animal** temp = new Animal*[m_numOfAnimals + 1];
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		temp[i] = m_animals[i];
	}
	temp[m_numOfAnimals] = an->clone();
	m_numOfAnimals++;
	m_animals = temp;
};//creates a copy of "an" (deep copy) and adds an animal to the array

Zoo& Zoo::operator+(Animal* an) {
	Animal** temp = new Animal*[m_numOfAnimals + 1];
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		temp[i] = m_animals[i];
	}
	temp[m_numOfAnimals] = an;
	m_numOfAnimals++;
	m_animals = temp;
	return *this;
};//adds an animal (only pointer, no copy needed) to the class and returns this with the change
Zoo Zoo::operator+(const Zoo& other) const {
	Zoo temp(*this);
	for (int i = 0; i < other.m_numOfAnimals; i++)
	{
		temp.AddAnimal(other.m_animals[i]);
	}
	return temp;
}; //returns a new Zoo with the properties of this and animals of this and other (need to deep copy the data of other)

void Zoo::Save(ofstream& ofs) const {
	ofs << strlen(m_name) << endl;
	ofs << m_name << endl;
	ofs << strlen(m_address) << endl;
	ofs << m_address << endl;
	ofs << m_ticketPrice << endl;
	ofs << strlen(m_openHours) << endl;
	ofs << m_openHours << endl;
	ofs << strlen(m_closeHours) << endl;
	ofs << m_closeHours << endl;
	ofs << m_numOfAnimals << endl;
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		m_animals[i] -> Save(ofs); // TODO
	}
};//method to save the info to a text file
void Zoo::Load(ifstream& ifs) {};//method to load the info from a text file
void Zoo::SaveBin(ofstream& ofs) const {};//method to save the info to a binary file

#pragma endregion