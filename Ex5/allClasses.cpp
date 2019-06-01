// Hadar Dayan (Id 206041444)
#include "allClasses.h"
#define MAX_STR 60

using namespace std;

// *************** Animal ************* //
#pragma region Animal
Animal::Animal() : m_childCount(0), m_avgLifetime(0), m_color(NULL) {
	m_color = new char[5];
	strcpy(m_color, "GRAY");
};
Animal::Animal(const char* color, int childs, float avgLifetime) : m_childCount(0), m_avgLifetime(0), m_color(NULL) {
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

Animal::~Animal() {};

Animal* Animal::clone() {
	return new Animal(m_color, m_childCount, m_avgLifetime);
};
void Animal::Save(ofstream& ofs) const {
	// save runtime object type
	ofs << typeid(*this).name() + 1 << endl;

	// save color, childs, avgLifetime
	ofs << m_color << endl;
	ofs << m_childCount << endl;
	ofs << m_avgLifetime << endl;
};//method to save the info to a text file
void Animal::Load(ifstream& ifs) {
	// load color
	m_color = new char[MAX_STR];
	ifs.getline(m_color, MAX_STR);

	//load childs, avgLifeTime
	ifs >> m_childCount;
	ifs >> m_avgLifetime;
};//method to load the info from a text file
void Animal::SaveBin(ofstream& ofs) const {
	int len = strlen(typeid(*this).name()) - 1;
	ofs.write((char*)&len, sizeof(len));
	ofs.write(typeid(*this).name() + 1, len);
	len = strlen(m_color);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_color, len);
	ofs.write((char*)&m_childCount, sizeof(m_childCount));
	ofs.write((char*)&m_avgLifetime, sizeof(m_avgLifetime));
};//method to save the info to a binary file

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
Mammals::Mammals(const char* color, int childs, float avgLifetime, float preg, float milk) 
	: Animal::Animal(color, childs, avgLifetime)
{
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
void Mammals::Save(ofstream& ofs) const {
	ofs << m_pregnancyTime << endl;
	ofs << m_milkLiters << endl;
};//method to save the info to a text file
void Mammals::Load(ifstream& ifs) {
	ifs >> m_pregnancyTime;
	ifs >> m_milkLiters;
};//method to load the info from a text file
void Mammals::SaveBin(ofstream& ofs) const {
	ofs.write((char*)&m_pregnancyTime, sizeof(m_pregnancyTime));
	ofs.write((char*)&m_milkLiters, sizeof(m_milkLiters));
};//method to save the info to a binary file

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
Birds::Birds(const char* color, int childs, float avgLifetime, float incubation):
	Animal(color, childs, avgLifetime)
{
	m_incubationTime = incubation;
};//init the Birds with a given attributes
Birds::Birds(ifstream& in_file) : Animal(in_file) {
	in_file.read((char*)&m_incubationTime, sizeof(m_incubationTime));
};//init the Birds from a binary file

Birds::~Birds() {};

Animal* Birds::clone() {
	return new Birds(m_color, m_childCount, m_avgLifetime, m_incubationTime);
};
void Birds::Save(ofstream& ofs) const {
	ofs << m_incubationTime << endl;
};//method to save the info to a text file
void Birds::Load(ifstream& ifs) {
	ifs >> m_incubationTime;
};//method to load the info from a text file
void Birds::SaveBin(ofstream& ofs) const {
	ofs.write((char*)&m_incubationTime, sizeof(m_incubationTime));
};//method to save the info to a binary file

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
void Fish::Save(ofstream& ofs) const {
	ofs << m_finCount << endl;
	ofs << m_gillsCount << endl;
};//method to save the info to a text file
void Fish::Load(ifstream& ifs) {
	ifs >> m_finCount;
	ifs >> m_gillsCount;
};//method to load the info from a text file
void Fish::SaveBin(ofstream& ofs) const {
	ofs.write((char*)&m_finCount, sizeof(m_finCount));
	ofs.write((char*)&m_gillsCount, sizeof(m_gillsCount));
};//method to save the info to a binary file

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
Horse::Horse(const char* color, int childs, float avgLifetime, float preg, float milk, const char* type) 
	: Animal(color, childs, avgLifetime),
	  Mammals(color, childs, avgLifetime, preg, milk) {
	m_type = new char[strlen(type) + 1];
	strcpy(m_type, type);
};//init the Horse with a given attributes
Horse::Horse(ifstream& in_file) : Animal(in_file), Mammals(in_file) {
	int len;
	in_file.read((char*)&len, sizeof(len));
	m_type = new char[len + 1];
	in_file.read(m_type, len);
	m_type[len] = '\0';
};//init the Horse from a binary file
Horse::~Horse() { };

Animal* Horse::clone() {
	return new Horse(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_type);
};
void Horse::Save(ofstream& ofs) const {
	Animal::Save(ofs);
	Mammals::Save(ofs);
	ofs << m_type << endl;
};//method to save the info to a text file
void Horse::Load(ifstream& ifs) {
	Animal::Load(ifs);
	Mammals::Load(ifs);
	m_type = new char[MAX_STR];
	ifs.ignore();
	ifs.getline(m_type, MAX_STR);
};//method to load the info from a text file
void Horse::SaveBin(ofstream& ofs) const {
	Animal::SaveBin(ofs);
	Mammals::SaveBin(ofs);
	int len = strlen(m_type);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_type, len);
};//method to save the info to a binary file

const char* Horse::GetType() const { return m_type; };//return the type of the horse

#pragma endregion

// *************** Flamingo ************* //
#pragma region Flamingo
Flamingo::Flamingo() { m_avgHeight = 0; };//set the default color to GRAY and other params to 0
Flamingo::Flamingo(const char* color, int childs, float avgLifetime, float incubation, float avgHeight) 
	: Animal(color, childs, avgLifetime), 
	  Birds(color, childs, avgLifetime, incubation) {
	m_avgHeight = avgHeight;
};//init the Flamingo with a given attributes
Flamingo::Flamingo(ifstream& in_file) : Animal(in_file),Birds(in_file) {
	in_file.read((char*)&m_avgHeight, sizeof(m_avgHeight));
};//init the Flamingo from a binary file
Flamingo::~Flamingo() {};

Animal* Flamingo::clone() {
	return new Flamingo(m_color, m_childCount, m_avgLifetime, m_incubationTime, m_avgHeight);
};
void Flamingo::Save(ofstream& ofs) const {
	Animal::Save(ofs);
	Birds::Save(ofs);
	ofs << m_avgHeight << endl;
};//method to save the info to a text file
void Flamingo::Load(ifstream& ifs) {
	Animal::Load(ifs);
	Birds::Load(ifs);
	ifs >> m_avgHeight;
};//method to load the info from a text file
void Flamingo::SaveBin(ofstream& ofs) const {
	Animal::SaveBin(ofs);
	Birds::SaveBin(ofs);
	ofs.write((char*)&m_avgHeight, sizeof(m_avgHeight));
};//method to save the info to a binary file

float Flamingo::GetHeight() const { return m_avgHeight; };//return the avg height of the flamingo

#pragma endregion


// *************** MammalsFish ************* //
#pragma region MammalsFish
MammalsFish::MammalsFish() : Animal() {};//set the default color to GRAY and other params to 0
MammalsFish::MammalsFish(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills)
	: Animal(color, childs, avgLifetime),
	  Mammals(color, childs, avgLifetime, preg, milk),
	  Fish(color, childs, avgLifetime, fin, gills)
{};//init the MammalsFish with a given attributes
MammalsFish::MammalsFish(ifstream& in_file) : Animal(in_file), Mammals(in_file), Fish(in_file) {};//init the MammalsFish from a binary file

MammalsFish::~MammalsFish() {};

Animal* MammalsFish::clone() {
	return new MammalsFish(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_finCount, m_gillsCount);
};
void MammalsFish::Save(ofstream& ofs) const {
	Animal::Save(ofs);
	Mammals::Save(ofs);
	Fish::Save(ofs);
};//method to save the info to a text file
void MammalsFish::Load(ifstream& ifs) {
	Animal::Load(ifs);
	Mammals::Load(ifs);
	Fish::Load(ifs);
};//method to load the info from a text file
void MammalsFish::SaveBin(ofstream& ofs) const {
	Animal::SaveBin(ofs);
	Mammals::SaveBin(ofs);
	Fish::SaveBin(ofs);
};//method to save the info to a binary file

#pragma endregion

// *************** GoldFish ************* //
#pragma region GoldFish
GoldFish::GoldFish() {
	m_avgWeight = 0;
	m_avgLength = 0;
};//set the default color to GRAY and other params to 0
GoldFish::GoldFish(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills, float avgW, float avgL) 
	: Animal(color, childs, avgLifetime),
	  MammalsFish(color, childs, avgLifetime, preg, milk, fin, gills) {
	m_avgWeight = avgW;
	m_avgLength = avgL;
};//init the GoldFish with a given attributes
GoldFish::GoldFish(ifstream& in_file) : Animal(in_file), MammalsFish(in_file) {
	in_file.read((char*)&m_avgWeight, sizeof(m_avgWeight));
	in_file.read((char*)&m_avgLength, sizeof(m_avgLength));
};//init the GoldFish from a binary file
GoldFish::~GoldFish() {};

Animal* GoldFish::clone() {
	return new GoldFish(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_finCount, m_gillsCount, m_avgWeight, m_avgLength);
};
void GoldFish::Save(ofstream& ofs) const {
	MammalsFish::Save(ofs);
	ofs << m_avgWeight << endl;
	ofs << m_avgLength << endl;
};//method to save the info to a text file
void GoldFish::Load(ifstream& ifs) {
	MammalsFish::Load(ifs);
	ifs >> m_avgWeight;
	ifs >> m_avgLength;
};//method to load the info from a text file
void GoldFish::SaveBin(ofstream& ofs) const {
	MammalsFish::SaveBin(ofs);
	ofs.write((char*)&m_avgWeight, sizeof(m_avgWeight));
	ofs.write((char*)&m_avgLength, sizeof(m_avgLength));
};//method to save the info to a binary file

float GoldFish::GetWeight() const { return m_avgWeight; };//return the avg weight of the gold fish
float GoldFish::GetLength() const { return m_avgLength; };//return the avg length of the gold fish
#pragma endregion


// *************** Mermaid ************* //
#pragma region Mermaid

Mermaid::Mermaid() {
	m_firstName = NULL;
	m_lastName = NULL;
};//set the default color to GRAY and other params to 0
Mermaid::Mermaid(const char* color, int childs, float avgLifetime, float preg, float milk, int fin, int gills, const char* firstName, const char* lastName) 
	: Animal(color, childs, avgLifetime),
	  MammalsFish(color, childs, avgLifetime, preg, milk, fin, gills) {
	m_firstName = new char[strlen(firstName) + 1];
	strcpy(m_firstName, firstName);
	m_lastName = new char[strlen(lastName) + 1];
	strcpy(m_lastName, lastName);
};//init the Mermaid with a given attributes
Mermaid::Mermaid(ifstream& in_file) : Animal(in_file), MammalsFish(in_file) {
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
Mermaid::~Mermaid() {};

Animal* Mermaid::clone() {
	return new Mermaid(m_color, m_childCount, m_avgLifetime, m_pregnancyTime, m_milkLiters, m_finCount, m_gillsCount, m_firstName, m_lastName);
};
void Mermaid::Save(ofstream& ofs) const {
	MammalsFish::Save(ofs);
	ofs << m_firstName << endl;
	ofs << m_lastName << endl;
};//method to save the info to a text file
void Mermaid::Load(ifstream& ifs) {
	MammalsFish::Load(ifs);

	m_firstName = new char[MAX_STR];
	m_lastName = new char[MAX_STR];

	ifs >> m_firstName;
	ifs >> m_lastName;
};//method to load the info from a text file
void Mermaid::SaveBin(ofstream& ofs) const {
	MammalsFish::SaveBin(ofs);
	int len = strlen(m_firstName);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_firstName, len);

	len = strlen(m_lastName);
	ofs.write((char*)&len, sizeof(len));
	ofs.write(m_lastName, len);
};//method to save the info to a binary file

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

	m_numOfAnimals = 0;
	m_animals = new Animal*[m_numOfAnimals];
	for (int i = 0; i < other.m_numOfAnimals; i++)
	{
		AddAnimal(other.m_animals[i]);
	}
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
		type[len] = '\0';
		if (strcmp(type, "Horse") == 0)
			m_animals[i] = new Horse(in_file);
		if (strcmp(type, "Flamingo") == 0)
			m_animals[i] = new Flamingo(in_file);
		if (strcmp(type, "GoldFish") == 0)
			m_animals[i] = new GoldFish(in_file);
		if (strcmp(type, "Mermaid") == 0)
			m_animals[i] = new Mermaid(in_file);
		delete type;
	}
};//c'tor that gets a binary file and loads the data of the zoo from the file
Zoo::~Zoo() {};//d'tor


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
Zoo& Zoo::operator+=(Animal* an) {
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
	int len = m_numOfAnimals + other.GetNumOfAnimals();
	Animal ** tmpAns = new Animal*[len];
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		tmpAns[i] = m_animals[i];
	}
	temp.m_animals = tmpAns;
	for (int i = 0; i < other.m_numOfAnimals; i++)
	{
		temp.AddAnimal(other.m_animals[i]);
	}
	return temp;
}; //returns a new Zoo with the properties of this and animals of this and other (need to deep copy the data of other)

void Zoo::Save(ofstream& ofs) const {
	ofs << m_name << endl;
	ofs << m_address << endl;
	ofs << m_ticketPrice << endl;
	ofs << m_openHours << endl;
	ofs << m_closeHours << endl;
	ofs << m_numOfAnimals << endl;
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		m_animals[i]->Save(ofs); // TODO
	}
};//method to save the info to a text file
void Zoo::Load(ifstream& ifs) {
	m_name = new char[MAX_STR];
	m_address = new char[MAX_STR];
	m_openHours = new char[MAX_STR];
	m_closeHours = new char[MAX_STR];

	ifs.getline(m_name, MAX_STR);
	ifs.getline(m_address, MAX_STR);
	ifs >> m_ticketPrice;
	ifs.ignore();
	ifs.getline(m_openHours, MAX_STR);
	ifs.getline(m_closeHours, MAX_STR);
	ifs >> m_numOfAnimals;
	ifs.ignore();

	m_animals = new Animal*[m_numOfAnimals];
	char* type = new char[MAX_STR];
	for (int i = 0; i < m_numOfAnimals; i++)
	{
		ifs.getline(type, MAX_STR);
		if (strcmp(type, "Horse") == 0)
			m_animals[i] = new Horse();
		if (strcmp(type, "Flamingo") == 0)
			m_animals[i] = new Flamingo();
		if (strcmp(type, "GoldFish") == 0)
			m_animals[i] = new GoldFish();
		if (strcmp(type, "Mermaid") == 0)
			m_animals[i] = new Mermaid();
		m_animals[i]->Load(ifs);
	}
	delete type;
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
		m_animals[i]->SaveBin(ofs); // TODO
	}
};//method to save the info to a binary file

#pragma endregion


ofstream& operator<<(ofstream& out, const Zoo& z) {
	z.Save(out);
	return out;
};
ifstream& operator>>(ifstream& in, Zoo& z) {
	z.Load(in);
	return in;
};
