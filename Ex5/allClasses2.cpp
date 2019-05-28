#include "allClasses.h"

using namespace std;

// *************** Animal ************* //
#pragma region Animal
Animal::Animal() : m_childCount(0), m_avgLifetime(0), m_color(NULL) {
	m_color = new char[4];
	strcpy(m_color, "GRAY");
};
Animal::Animal(Animal * an) : m_childCount(an->m_childCount), m_avgLifetime(an->m_avgLifetime), m_color(NULL) {
	m_color = new char[strlen(an->m_color)];
	strcpy(m_color, an->m_color);
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
	delete m_color;
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

ofstream& Animal::SaveBin(ofstream& out_file) {
	int len = strlen(typeid(*this).name() + 6);
	char* type = new char[len];
	strncpy(type, typeid(*this).name() + 6, len);
	out_file.write((char*)type, len);
	len = strlen(m_color);
	out_file.write((char*)&len, sizeof(len));
	out_file.write(m_color, len);
	out_file.write((char*)&m_childCount, sizeof(m_childCount));
	out_file.write((char*)&m_avgLifetime, sizeof(m_avgLifetime));
	return out_file;
};// init the Animal from a binary file
ofstream& Animal::operator<<(ofstream& out_file) {
	out_file << strlen(typeid(*this).name() + 6) << endl;
	out_file << typeid(*this).name() + 6 << endl;
	out_file << strlen(m_color) << endl;
	out_file << m_color << endl;
	out_file << m_childCount << endl;
	out_file << m_avgLifetime << endl;
	return out_file;
}
ifstream& Animal::LoadBin(ifstream& in_file) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	char* type = new char[len + 1];
	in_file.read(type, len);
	type[len] = '\0';
	in_file.read((char*)&len, sizeof(len));
	m_color = new char[len + 1];
	in_file.read(m_color, len);
	m_color[len] = '\0';
	in_file.read((char*)&m_childCount, sizeof(m_childCount));
	in_file.read((char*)&m_avgLifetime, sizeof(m_avgLifetime));
	return in_file;
};// init the Animal from a binary file
ifstream& Animal::operator>>(ifstream& in_file) {
	int len;
	in_file >> len;
	char* type = new char[len + 1];
	in_file.getline(type, len);
	type[len] = '\0';
	in_file >> len;
	m_color = new char[len + 1];
	m_color = new char[len + 1];
	in_file.getline(m_color, len);
	m_color[len] = '\0';
	in_file >> m_childCount;
	in_file >> m_avgLifetime;
	return in_file;
}

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
Mammals::Mammals(ifstream& in_file): Animal::Animal(in_file) {
	in_file.read((char*)&m_pregnancyTime, sizeof(m_pregnancyTime));
	in_file.read((char*)&m_milkLiters, sizeof(m_milkLiters));
};//init the Mammals from a binary file

ofstream& Mammals::SaveBin(ofstream& out_file) {
	Animal::SaveBin(out_file);
	out_file.write((char*)&m_pregnancyTime, sizeof(m_pregnancyTime));
	out_file.write((char*)&m_milkLiters, sizeof(m_milkLiters));
};
ofstream& Mammals::operator<<(ofstream& out_file) {
	Animal::operator<< (out_file);
	out_file << m_pregnancyTime << endl;
	out_file << m_milkLiters << endl;
};
ifstream& Mammals::LoadBin(ifstream& in_file) {
	Animal::LoadBin(in_file);
	in_file.read((char*)&m_pregnancyTime, sizeof(m_pregnancyTime));
	in_file.read((char*)&m_milkLiters, sizeof(m_milkLiters));
};
ifstream& Mammals::operator>>(ifstream& in_file) {
	Animal::operator>> (in_file);
	in_file>>m_pregnancyTime;
	in_file>>m_milkLiters;
};


Mammals::~Mammals() {};

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
Birds::Birds(ifstream& in_file): Animal(in_file) {
	in_file.read((char*)&m_incubationTime, sizeof(m_incubationTime));
};//init the Birds from a binary file
ofstream& Birds::SaveBin(ofstream& out_file) {
	Animal::SaveBin(out_file);
	out_file.write((char*)&m_incubationTime, sizeof(m_incubationTime));
	return out_file;
};
//ofstream& Birds::operator<<(ofstream& out_file) {
//	Animal::operator<< (out_file);
//	out_file << m_incubationTime << endl;
//};
//ifstream& Birds::LoadBin(ifstream& in_file) {
//	Animal::LoadBin(in_file);
//	in_file.read((char*)&m_incubationTime, sizeof(m_incubationTime));
//};
//ifstream& Birds::operator>>(ifstream& in_file) {
//	Animal::operator>> (in_file);
//	in_file >> m_incubationTime;
//};
Birds::~Birds() {};
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
Fish::Fish(ifstream& in_file): Animal(in_file) {
	in_file.read((char*)&m_finCount, sizeof(m_finCount));
	in_file.read((char*)&m_gillsCount, sizeof(m_gillsCount));
};//init the Fish from a binary file
ofstream& Fish::SaveBin(ofstream& out_file) {
	Animal::SaveBin(out_file);
	out_file.write((char*)&m_finCount, sizeof(m_finCount));
	out_file.write((char*)&m_gillsCount, sizeof(m_gillsCount));
	return out_file;
};
ofstream& Fish::operator<<(ofstream& out_file) {
	Animal::operator<< (out_file);
	out_file << m_finCount << endl;
	out_file << m_gillsCount << endl;
};
ifstream& Fish::LoadBin(ifstream& in_file) {
	Animal::LoadBin(in_file);
	in_file.read((char*)&m_finCount, sizeof(m_finCount));
	in_file.read((char*)&m_gillsCount, sizeof(m_gillsCount));
};
ifstream& Fish::operator>>(ifstream& in_file) {
	Animal::operator>> (in_file);
	in_file >> m_finCount;
	in_file >> m_gillsCount;
};
Fish::~Fish() {};

int	Fish::GetFinCount() const {
	return m_finCount;
};//return the fin count of the animal
int	Fish::GetGillsCount() const {
	return m_gillsCount;
};//return the gills count of the animal

void Fish::SetFin(int fin) { m_finCount = fin; };
void Fish::SetGills(int gills) { m_gillsCount = gills; };
#pragma endregion

// *************** Horse ************* //
#pragma region Horse

Horse::Horse(): m_type(NULL) {};//set the default color to GRAY and other params to 0
Horse::Horse(const char* color, int childs, float avgLifetime, float preg, float milk, const char* type) : Mammals(color, childs, avgLifetime, preg, milk) {
	m_type = new char[strlen(type) +1];
	strcpy(m_type, type);
};//init the Horse with a given attributes
Horse::Horse(Animal * an): Animal(an) {
	Horse* horse = dynamic_cast<Horse*>(an);
	if (horse) {
		m_type = new char[strlen(horse->m_type)];
		strcpy(m_type, horse->m_type);
	}
};
Horse::Horse(ifstream& in_file) : Mammals(in_file) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_type = new char[len + 1];
	in_file.read(m_type, len);
	m_type[len] = '\0';
};//init the Horse from a binary file
ofstream& Horse::SaveBin(ofstream& out_file) {
	Mammals::SaveBin(out_file);
	int len = strlen(m_type);
	out_file.write((char*)&len, sizeof(len));
	out_file.write(m_type, len);
};
ofstream& Horse::operator<<(ofstream& out_file) {
	Mammals::operator<< (out_file);
	out_file << strlen(m_type) << endl;
	out_file << m_type << endl;
};
ifstream& Horse::LoadBin(ifstream& in_file) {
	Mammals::LoadBin(in_file);
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_type = new char[len + 1];
	in_file.read(m_type, len);
	m_type[len] = '\0';
};
ifstream& Horse::operator>>(ifstream& in_file) {
	Mammals::operator>> (in_file);
	int len;
	in_file >> len;
	char* type = new char[len + 1];
	in_file.getline(type, len);
	type[len] = '\0';
};
Horse::~Horse() { delete m_type; };

const char* Horse::GetType() const { return m_type; };//return the type of the horse

#pragma endregion

// *************** Flamingo ************* //
#pragma region Flamingo

Flamingo::Flamingo() { m_avgHeight = 0; };//set the default color to GRAY and other params to 0
Flamingo::Flamingo(const char* color, int childs, float avgLifetime, float incubation, float avgHeight) : Birds(color, childs, avgLifetime, incubation) {
	m_avgHeight = avgHeight;
};//init the Flamingo with a given attributes
Flamingo::Flamingo(Animal * an) : Animal(an) {
	Flamingo* flamingo = dynamic_cast<Flamingo*>(an);
	if (flamingo) {
		m_avgHeight = flamingo->m_avgHeight;
	}
};
Flamingo::Flamingo(ifstream& in_file) : Birds(in_file) {
	in_file.read((char*)&m_avgHeight, sizeof(m_avgHeight));
};//init the Flamingo from a binary file
ofstream& Flamingo::SaveBin(ofstream& out_file) {
	Birds::SaveBin(out_file);
	out_file.write((char*)&m_avgHeight, sizeof(m_avgHeight));
	return out_file;
};
ofstream& Flamingo::operator<<(ofstream& out_file) {
	Birds::operator<< (out_file);
	out_file << m_avgHeight << endl;
};
ifstream& Flamingo::LoadBin(ifstream& in_file) {
	Birds::LoadBin(in_file);
	in_file.read((char*)&m_avgHeight, sizeof(m_avgHeight));
};
ifstream& Flamingo::operator>>(ifstream& in_file) {
	Birds::operator>> (in_file);
	in_file >> m_avgHeight;
};
Flamingo::~Flamingo() {};

float Flamingo::GetHeight() const { return m_avgHeight; };//return the avg height of the flamingo

#pragma endregion


// *************** MammalsFish ************* //
#pragma region MammalsFish
MammalsFish::MammalsFish() {};//set the default color to GRAY and other params to 0
MammalsFish::MammalsFish(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills) : Animal(color, childs, avgLifetime), Mammals(color, childs, avgLifetime, preg, milk), Fish(color, childs, avgLifetime, fin, gills) {};//init the MammalsFish with a given attributes
MammalsFish::MammalsFish(ifstream& in_file) : Mammals(in_file), Fish(in_file) {};//init the MammalsFish from a binary file
ofstream& MammalsFish::SaveBin(ofstream& out_file) {
	Mammals::SaveBin(out_file);
	Fish::SaveBin(out_file);
};
ofstream& MammalsFish::operator<<(ofstream& out_file) {
	Mammals::operator<< (out_file);
	Fish::operator<< (out_file);
};
ifstream& MammalsFish::LoadBin(ifstream& in_file) {
	Mammals::LoadBin(in_file);
	Fish::LoadBin(in_file);
};

ifstream& MammalsFish::operator>>(ifstream& in_file) {
	Mammals::operator>> (in_file);
	Fish::operator>> (in_file);
};
MammalsFish::~MammalsFish() {};

#pragma endregion


// *************** GoldFish ************* //
#pragma region GoldFish
GoldFish::GoldFish() {
	m_avgWeight = 0;
	m_avgLength = 0;
};//set the default color to GRAY and other params to 0
GoldFish::GoldFish(Animal * an) : Animal(an) {
	GoldFish* goldFish = dynamic_cast<GoldFish*>(an);
	if (goldFish) {
		m_avgWeight = goldFish->m_avgWeight;
		m_avgLength = goldFish->m_avgLength;
	}
};
GoldFish::GoldFish(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills, float avgW, float avgL) : MammalsFish(color, childs, avgLifetime, preg, milk, fin, gills) {
	m_avgWeight = avgW;
	m_avgLength = avgL;
};//init the GoldFish with a given attributes
GoldFish::GoldFish(ifstream& in_file): MammalsFish(in_file) {
	in_file.read((char*)&m_avgWeight, sizeof(m_avgWeight));
	in_file.read((char*)&m_avgLength, sizeof(m_avgLength));
};//init the GoldFish from a binary file
ofstream& GoldFish::SaveBin(ofstream& out_file) {
	MammalsFish::SaveBin(out_file);
	out_file.write((char*)&m_avgWeight, sizeof(m_avgWeight));
	out_file.write((char*)&m_avgLength, sizeof(m_avgLength));
};
ofstream& GoldFish::operator<<(ofstream& out_file) {
	MammalsFish::operator<< (out_file);
	out_file << m_avgWeight << endl;
	out_file << m_avgLength << endl;
};
ifstream& GoldFish::LoadBin(ifstream& in_file) {
	MammalsFish::LoadBin(in_file);
	in_file.read((char*)&m_avgWeight, sizeof(m_avgWeight));
	in_file.read((char*)&m_avgLength, sizeof(m_avgLength));
};
ifstream& GoldFish::operator>>(ifstream& in_file) {
	MammalsFish::operator>> (in_file);
	in_file >> m_avgWeight;
	in_file >> m_avgLength;
};
GoldFish::~GoldFish() {};

float GoldFish::GetWeight() const { return m_avgWeight; };//return the avg weight of the gold fish
float GoldFish::GetLength() const { return m_avgLength; };//return the avg length of the gold fish
#pragma endregion


// *************** Mermaid ************* //
#pragma region Mermaid

Mermaid::Mermaid() {
	m_firstName = NULL;
	m_lastName = NULL;
};//set the default color to GRAY and other params to 0
Mermaid::Mermaid(Animal * an) : Animal(an) {
	Mermaid* mermaid = dynamic_cast<Mermaid*>(an);
	if (mermaid) {
		m_firstName = new char[strlen(mermaid->m_firstName)];
		strcpy(m_firstName, mermaid->m_firstName);		
		m_lastName = new char[strlen(mermaid->m_lastName)];
		strcpy(m_lastName, mermaid->m_lastName);
	}
};
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
	delete m_firstName;
	delete m_lastName;
};

ofstream& Mermaid::SaveBin(ofstream& out_file) {
	MammalsFish::SaveBin(out_file);
	int len = strlen(m_firstName);
	out_file.write((char*)&len, sizeof(len));
	out_file.write(m_firstName, len);
	len = strlen(m_lastName);
	out_file.write((char*)&len, sizeof(len));
	out_file.write(m_lastName, len);
};
/*ofstream& Mermaid::operator<<(ofstream& out_file) {
	MammalsFish::operator<< (out_file);
	out_file << strlen(m_firstName) << endl;
	out_file << m_firstName << endl;
	out_file << strlen(m_lastName) << endl;
	out_file << m_lastName << endl;
};*/
ifstream& Mermaid::LoadBin(ifstream& in_file) {
	MammalsFish::LoadBin(in_file);
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_firstName = new char[len + 1];
	in_file.read(m_firstName, len);
	m_firstName[len] = '\0';
	in_file.read((char*)&len, sizeof(len));
	m_lastName = new char[len + 1];
	in_file.read(m_lastName, len);
	m_lastName[len] = '\0';
};
//ifstream& Mermaid::operator>>(ifstream& in_file) {};
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
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
	m_address = new char[strlen(address) + 1];
	strcpy(m_address, address);
	m_ticketPrice = ticket;
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
	m_animals = new Animal*[other.m_numOfAnimals];
	for (int i = 0; i < other.m_numOfAnimals; i++)
	{
		m_animals[i] = other.m_animals[i];
	}
}
Zoo::Zoo(ifstream& in_file) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_name = new char[len + 1];
	in_file.read(m_name, len);
	m_name[len] = '/0';
	in_file.read((char*)&len, sizeof(len));
	m_address = new char[len + 1];
	in_file.read(m_address, len);
	m_address[len] = '/0';
	in_file.read((char*)&m_ticketPrice, sizeof(m_ticketPrice));
	in_file.read((char*)&len, sizeof(len));
	m_openHours = new char[len + 1];
	in_file.read(m_openHours, len);
	m_openHours[len] = '/0';
	in_file.read((char*)&len, sizeof(len));
	m_closeHours = new char[len + 1];
	in_file.read(m_closeHours, len);
	m_closeHours[len] = '/0'; 
	in_file.read((char*)&len, sizeof(len));
	for (int i = 0; i < len; i++)
	{
		int len;
		in_file.read((char*)&len, sizeof(len));
		char* type = new char[len + 1];
		in_file.read(type, len);
		type[len] = '\0';

		Animal* an;
		if (type == "Horse")
			an = new Horse(ifs);
		else if (type == "Flamingo")
			an = new Flamingo(ifs);
		else if (type == "GoldFish")
			an = new GoldFish(ifs);
		else if (type == "Mermaid")
			an = new Mermaid(ifs);
		AddAnimal(an);
	}

};//c'tor that gets a binary file and loads the data of the zoo from the file
Zoo::~Zoo() {
	delete m_name;
	delete m_address;
	delete m_openHours;
	delete m_closeHours;
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		delete m_animals[i];
	}
	delete[] m_animals;
};//d'tor

const char* Zoo::GetName() const { return m_name; };//return the name of the zoo
const char*	Zoo::GetAddress() const { return m_address; };//return the address of the zoo
float		Zoo::GetTicketPrice() const { return m_ticketPrice; };//return the ticket price of the zoo
const char*	Zoo::GetOpenHour() const { return m_openHours; };//return the open hour of the zoo
const char*	Zoo::GetCloseHour() const { return m_closeHours; };//return the close hour of the zoo
int			Zoo::GetNumOfAnimals() const { return m_numOfAnimals; };//return the num of animals in the zoo
Animal**	Zoo::GetAnimals() const { return m_animals; };//return the animals array of the zoo

void Zoo::AddAnimal(Animal* an) {
	Animal** temp = new Animal*[m_numOfAnimals +1];
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		temp[i] = m_animals[i];
	}
	string type = typeid(an).name() + 6;
	if (type == "Horse")
		temp[m_numOfAnimals] = new Horse(an);
	else if (type == "Flamingo")
		temp[m_numOfAnimals] = new Flamingo(an);
	else if (type == "GoldFish")
		temp[m_numOfAnimals] = new GoldFish(an);
	else if (type == "Mermaid")
		temp[m_numOfAnimals] = new MammalsFish(an);
	m_animals = temp;
	m_numOfAnimals++;
};//creates a copy of "an" (deep copy) and adds an animal to the array

Zoo& Zoo::operator+(Animal* an) {
	Animal** temp = new Animal*[m_numOfAnimals + 1];
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		temp[i] = m_animals[i];
	}
	temp[m_numOfAnimals] = an;
	m_animals = temp;
	m_numOfAnimals++;
	return *this;
};//adds an animal (only pointer, no copy needed) to the class and returns this with the change
Zoo& Zoo::operator+=(Animal* an) {
	Animal** temp = new Animal*[m_numOfAnimals + 1];
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		temp[i] = m_animals[i];
	}
	temp[m_numOfAnimals] = an;
	m_animals = temp;
	m_numOfAnimals++;
	return *this;
};//adds an animal (only pointer, no copy needed) to the class and returns this with the change
Zoo Zoo::operator+(const Zoo& other) const {
	Zoo newZoo(*this);
	for (int i = 0; i < other.m_numOfAnimals; i++)
	{
		newZoo.AddAnimal(other.m_animals[i]);
	}
	return newZoo;
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
		ofs << m_animals[i];
	}
};//method to save the info to a text file
void Zoo::Load(ifstream& ifs) {
	int len;
	ifs.getline((char*)&len, sizeof(len));
	m_name = new char[len + 1];
	ifs.getline(m_name, sizeof(m_name));
	m_name[len] = '\0';
	ifs.getline((char*)&len, sizeof(len));
	m_address = new char[len + 1];
	ifs.getline(m_address, sizeof(m_address));
	m_address[len] = '\0';
	ifs.getline((char*)&m_ticketPrice, sizeof(m_ticketPrice));
	ifs.getline((char*)&len, sizeof(len));
	m_openHours = new char[len + 1];
	ifs.getline(m_openHours, sizeof(m_openHours));
	m_openHours[len] = '\0';
	ifs.getline((char*)&len, sizeof(len));
	m_closeHours = new char[len + 1];
	ifs.getline(m_closeHours, sizeof(m_closeHours));
	m_closeHours[len] = '\0';
	m_numOfAnimals = 0;
	m_animals = NULL;
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		int len;
		ifs >> len;
		char* type = new char[len + 1];
		ifs.getline(type, len);
		type[len] = '\0';

		Animal* an;
		if (type == "Horse") 
			an = new Horse(ifs);
		else if (type == "Flamingo")
			an = new Flamingo(ifs);
		else if (type == "GoldFish")
			an = new GoldFish(ifs);
		else if (type == "Mermaid")
			an = new Mermaid(ifs);
		AddAnimal(an);
	}
};//method to load the info from a text file
void Zoo::SaveBin(ofstream& ofs) const {
	int len = strlen(m_name);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_name, len);
	len = strlen(m_address);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_address, len);
	ofs.write((char*)&m_ticketPrice, sizeof(m_ticketPrice));
	len = strlen(m_openHours);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_openHours, len);
	len = strlen(m_closeHours);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_closeHours, len);
	ofs.write((char*)&m_numOfAnimals, sizeof(m_numOfAnimals));
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		m_animals[i] -> SaveBin(ofs);
	}
};//method to save the info to a binary file
//ofstream& Zoo::operator<<(ofstream& out_file) {
//	Save(out_file);
//	return out_file;
//};
void Zoo::LoadBin(ifstream& in_file) {
	//return in_file;
};
//ifstream& Zoo::operator>>(ifstream& in_file) {
//	Load(in_file);
//	return in_file;
//};

#pragma endregion


ofstream& operator<<(ofstream& out, const Zoo& z) {
	z.Save(out);
	return out;
};
ifstream& operator>>(ifstream& in, Zoo& z) {
	z.Load(in);
	return in;
};

ofstream& operator<<(ofstream& out, const Mermaid& m) {
	MammalsFish::operator<< (out_file);
	out_file << strlen(m_firstName) << endl;
	out_file << m_firstName << endl;
	out_file << strlen(m_lastName) << endl;
	out_file << m_lastName << endl;
};
ifstream& operator>>(ifstream& in, Mermaid& m) {};


ofstream& operator<<(ofstream& out, const GoldFish& gf);
ifstream& operator>>(ifstream& in, GoldFish& gf);

ofstream& operator<<(ofstream& out, const MammalsFish& mf);
ifstream& operator>>(ifstream& in, MammalsFish& mf);

ofstream& operator<<(ofstream& out, const Flamingo& f);
ifstream& operator>>(ifstream& in, Flamingo& f);

ofstream& operator<<(ofstream& out, const Horse& h);
ifstream& operator>>(ifstream& in, Horse& h);

ofstream& operator<<(ofstream& out, const Fish& f);
ifstream& operator>>(ifstream& in, Fish& f);

ofstream& operator<<(ofstream& out, const Birds& b);
ifstream& operator>>(ifstream& in, Birds& b);

ofstream& operator<<(ofstream& out, const Mammals& m);
ifstream& operator>>(ifstream& in, Mammals& m);

ofstream& operator<<(ofstream& out, const Animal& a);
ifstream& operator>>(ifstream& in, Animal& a);