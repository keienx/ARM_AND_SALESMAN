#pragma once
#include "header.h"

template <typename T>
class graph{
public:
	graph();
	~graph();
	size_t size() {
		return this->_size;
	}
	void addVertex(T data);
	void addEdge(T data_v1, T data_v2, int weight);
	void addEdge(size_t v1, size_t v2, int weight);
	void addDirectEdge(T v_start, T v_finish, int weight);
	void addDirectEdge(size_t start, size_t finish, int weight);
	void removeVertex(T data);
	void removeEdge(T data_v1, T data_v2);
	void removeEdge(size_t v1, size_t v2);
	vector<T> getVertexData() {
		return this->data;
	}

	void calcCordEdge(vector<sf::RectangleShape>& vec, vector<sf::ConvexShape>& v_direction, const vector<sf::CircleShape>& vert);
	void calcCordText(vector<sf::Text>& v_text, const vector<sf::CircleShape>& vert, sf::Text& text);
	void calcCordWeight(vector<sf::Text>& v_weight, const vector<sf::CircleShape>& vert, sf::Text& text);
	
	void SalesmanTravel(const int& start);
	list<int> getPath() {
		return this->pathh;
	}
	int getPathWeight() {
		return this->pathWeight;
	}
	void clearPath() { 
		this->pathh.clear();
	}

private:
	bool AllVisited(std::vector<bool>& visitedVerts);
	std::vector<int> getNeighbours(const int& vert);
	void mainSalesman(const int& start, const int& current, std::list<int>& path, std::vector<bool>& visitedVerts);
	int pathWeight;

	size_t _size;
	vector<T> data;
	vector<vector <int>> matrix;
	list<int> pathh;
};

template<typename T>
inline std::vector<int> graph<T>::getNeighbours(const int& vert){

	std::list<int> result;
	for (int j = 0; j < this->data.size(); ++j){
		if (this->matrix[vert][j] != 0 && this->matrix[vert][j] != INT_MAX){
			result.push_back(j);
		}
	}
	return std::vector<int>(result.begin(), result.end());
}

template<typename T>
inline void graph<T>::SalesmanTravel(const int& start){
	this->pathh.clear();
	this->pathWeight = INT_MAX;
	std::list<int> path;
	path.clear();
	path.push_back(start);
	std::vector<bool> vis(this->data.size(), false);
	vis[start] = true;
	this->mainSalesman(start, start, path, vis);
}

template<typename T>
inline bool graph<T>::AllVisited(std::vector<bool>& visitedVerts){
	bool flag = true;
	for (int i = 0; i < this->data.size(); i++) {
		if (visitedVerts[i] != true) {
			flag = false;
		}
	}
	return flag;
};

template<typename T>
inline void graph<T>::mainSalesman(const int& start, const int& current, std::list<int>& path, std::vector<bool>& visitedVerts){
	if (this->AllVisited(visitedVerts)){
		int min = 0;
		if (!this->matrix[current][start]){
			return;
		}

		std::vector<int> p(path.begin(), path.end());
		for (int i = 0; i < p.size() - 1; ++i){
			min += this->matrix[p[i]][p[i + 1]];
		}
		min += this->matrix[current][start];
		if (this->pathWeight >= min){
			this->pathWeight = min;
			this->pathh = path;
		}
	}

	std::vector<int> nbrs = this->getNeighbours(current);

	for (int& i : nbrs){
		if (!visitedVerts[i]){
			std::vector<bool> cpy_vis(visitedVerts.begin(), visitedVerts.end());
			std::list<int> path_cpy(path.begin(), path.end());
			cpy_vis[i] = true;
			path_cpy.push_back(i);
			mainSalesman(start, i, path_cpy, cpy_vis);
		}
	};

}

template<typename T>
inline graph<T>::graph(){
	matrix.reserve(10);
	data.reserve(10);
	_size = 0;
	pathWeight = INT_MAX;
}

template<typename T>
inline void graph<T>::addVertex(T data){
	this->data.push_back(data);
	++this->_size;		

	vector<int> vec(this->data.size(), 0);
	vec[_size - 1] = INT_MAX;
	for (auto& i : this->matrix) {
		i.push_back(0);
	}

	this->matrix.push_back(vec);
}

template<typename T>
inline void graph<T>::addEdge(T data_v1, T data_v2, int weight){
	auto it1 = find(this->data.begin(), this->data.end(), data_v1);
	auto it2 = find(this->data.begin(), this->data.end(), data_v2);
	if (it1 == this->data.end() || it2 == this->data.end()) return;
	addEdge(size_t(distance(this->data.begin(), it1)), size_t(distance(this->data.begin(), it2)), weight);
}

template<typename T>
void graph<T>::addEdge(size_t v1, size_t v2, int weight){
	if (v1 == v2) return;
	this->matrix[v1][v2] = weight;
	this->matrix[v2][v1] = weight;
}

template<typename T>
inline void graph<T>::addDirectEdge(T v_start, T v_finish, int weight){
	auto it1 = find(this->data.begin(), this->data.end(), v_start);
	auto it2 = find(this->data.begin(), this->data.end(), v_finish);
	if (it1 == this->data.end() || it2 == this->data.end()) return;
	addDirectEdge(size_t(distance(this->data.begin(), it1)), size_t(distance(this->data.begin(), it2)), weight);
}

template<typename T>
inline void graph<T>::addDirectEdge(size_t start, size_t finish, int weight){
	if (start == finish) return;
	this->matrix[start][finish] = weight;
}

template<typename T>
inline void graph<T>::removeVertex(T data){
	auto it1 = find(this->data.begin(), this->data.end(), data);
	if (it1 == this->data.end()) return;
	this->matrix.erase(matrix.begin() + distance(this->data.begin(), it1));
	for (int i = 0; i < this->matrix.size(); ++i)
		this->matrix[i].erase(this->matrix[i].begin() + distance(this->data.begin(), it1));
	this->data.erase(it1);
	--this->_size;
}

template<typename T>
inline void graph<T>::removeEdge(T data_v1, T data_v2){
	auto it1 = find(this->data.begin(), this->data.end(), data_v1);
	auto it2 = find(this->data.begin(), this->data.end(), data_v2);
	if (it1 == this->data.end() || it2 == this->data.end()) return;
	removeEdge(size_t(distance(this->data.begin(), it1)), size_t(distance(this->data.begin(), it2)));
}

template<typename T>
inline void graph<T>::removeEdge(size_t v1, size_t v2){
	if (v1 == v2) return;
	this->matrix[v1][v2] = 0;
	this->matrix[v2][v1] = 0;
}

template<typename T>
inline void graph<T>::calcCordEdge(vector<sf::RectangleShape>& edges, vector<sf::ConvexShape>& v_direction, const vector<sf::CircleShape>& vert){
	edges.clear();
	v_direction.clear();

	if (this->matrix.size() == 0) return;

	float length, angle;

	float width, height;

	sf::ConvexShape triangle_trash(3);
	triangle_trash.setPoint(0, sf::Vector2f(0, 0));
	triangle_trash.setPoint(1, sf::Vector2f(0, 0));
	triangle_trash.setPoint(2, sf::Vector2f(0, 0));

	sf::ConvexShape triangle(3);
	triangle.setPoint(0, sf::Vector2f(0, 0));
	triangle.setPoint(1, sf::Vector2f(25, 0));
	triangle.setPoint(2, sf::Vector2f(14, 25));
	triangle.setFillColor(sf::Color::Magenta);
	triangle.setOutlineThickness(0);
	
	float x, y, k, b, t;
	sf::Vector2f center1;
	sf::Vector2f center2;


	sf::Vector2f temp;
	size_t row = 0, column = 1;

	while (row < this->_size - 1)	{
		while (column < this->_size){
			if (this->matrix[row][column] == 0 && this->matrix[column][row] == 0)
				++column;
			else if (this->matrix[column][row] != 0){
				temp = vert[column].getPosition() - vert[row].getPosition();
				length = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
				angle = atan2(temp.y, temp.x) * 180 / 3.14159;

				sf::RectangleShape line(sf::Vector2f(length, 3.f));

				line.setPosition(vert[row].getPosition());
				line.setRotation(angle);
				line.setFillColor(sf::Color::Green);
				edges.push_back(line);
				if (this->matrix[row][column] == 0){
					center1 = vert[column].getPosition();
					center2 = vert[row].getPosition();	
					k = (center2.y - center1.y) / (center2.x - center1.x);
					b = center1.y - k * center1.x;
					t = 1 - (55 / length);
					x = center1.x + t * (center2.x - center1.x);
					y = center1.y + t * (center2.y - center1.y);
					width = triangle.getLocalBounds().width;		
					height = triangle.getLocalBounds().height;
					triangle.setOrigin(width / 2.0f, height / 2.0f);
					triangle.setRotation(angle + 90);
					triangle.setPosition(x, y);
					v_direction.push_back(triangle);
				}
				else{
					v_direction.push_back(triangle_trash);
				}
				++column;
			}
			else{
				temp = vert[row].getPosition() - vert[column].getPosition();
				length = sqrt(pow(temp.x, 2) + pow(temp.y, 2));	
				angle = atan2(temp.y, temp.x) * 180 / 3.14159;

				sf::RectangleShape line(sf::Vector2f(length, 3.f));	

				line.setPosition(vert[column].getPosition());
				line.setRotation(angle);
				line.setFillColor(sf::Color::Green);
				edges.push_back(line);
				if (this->matrix[column][row] == 0){
					center1 = vert[row].getPosition();
					center2 = vert[column].getPosition();
					k = (center2.y - center1.y) / (center2.x - center1.x);
					b = center1.y - k * center1.x;
					t = 1 - (50 / length);
					x = center1.x + t * (center2.x - center1.x);
					y = center1.y + t * (center2.y - center1.y);
					width = triangle.getLocalBounds().width;
					height = triangle.getLocalBounds().height;
					triangle.setOrigin(width / 2.0f, height / 2.0f);
					triangle.setRotation(angle + 90);
					triangle.setPosition(x, y);
					v_direction.push_back(triangle);
				}
				else{
					v_direction.push_back(triangle_trash);
				}
				++column;
			}
		}
		++row;
		column = row + 1;
	}
}

template<typename T>
inline void graph<T>::calcCordText(vector<sf::Text>& v_text, const vector<sf::CircleShape>& vert, sf::Text& text){
	float width, height;
	v_text.clear();
	string str;
	for (int i = 0; i < this->data.size(); i++){
		str = this->data[i];
		text.setString(str);

		width = text.getLocalBounds().width;
		height = text.getLocalBounds().height;
		text.setOrigin(width / 2.0f, height / 2.0f);
		text.setPosition(vert[i].getPosition().x, vert[i].getPosition().y - 5);	//
		v_text.push_back(text);
	}
}

template<typename T>
inline void graph<T>::calcCordWeight(vector<sf::Text>& v_weight, const vector<sf::CircleShape>& vert, sf::Text& text){
	if (vert.size() == 0) return;
	v_weight.clear();
	string str;
	float x1, y1, x2, y2, midX, midY;
	float width = 0, height = 0;
	size_t row = 0, column = 1;
	while (row < this->_size - 1){
		while (column < this->_size){
			if (this->matrix[row][column] == 0 && this->matrix[column][row] == 0) {
				++column;
			}
			else if (this->matrix[column][row] != 0){
				str = to_string(this->matrix[column][row]);
				str = str.substr(0, str.length() - 7);
				text.setString(str);
				x1 = vert[column].getPosition().x;
				y1 = vert[column].getPosition().y;
				x2 = vert[row].getPosition().x;
				y2 = vert[row].getPosition().y;
				midX = (x1 + x2) / 2;
				midY = (y1 + y2) / 2;
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.width / 2, textRect.height / 2);
				text.setPosition(midX, midY);
				v_weight.push_back(text);
				++column;
			}
			else{
				str = to_string(this->matrix[row][column]);
				str = str.substr(0, str.length() - 7);
				text.setString(str);
				x1 = vert[row].getPosition().x;
				y1 = vert[row].getPosition().y;
				x2 = vert[column].getPosition().x;
				y2 = vert[column].getPosition().y;
				midX = (x1 + x2) / 2;
				midY = (y1 + y2) / 2;
				sf::FloatRect textRect = text.getLocalBounds();
				text.setOrigin(textRect.width / 2, textRect.height / 2);
				text.setPosition(midX, midY);
				v_weight.push_back(text);
				++column;
			}
		}
		++row;
		column = row + 1;
	}

}

template<typename T>
graph<T>::~graph(){
	this->_size = 0;
	this->data.clear();
	this->matrix.clear();
}