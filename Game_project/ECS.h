#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID get_new_component_type_ID() {
	static ComponentID last_ID = 0u;
	return last_ID++;
}

template <typename T> inline ComponentID get_component_type_ID() noexcept {
	static ComponentID type_ID = get_new_component_type_ID();
	return type_ID;
}

constexpr std::size_t max_components = 32;
constexpr std::size_t max_groups = 32;

using ComponentBitSet = std::bitset<max_components>;
using GroupBitSet = std::bitset<max_groups>;
using ComponentArray = std::array<Component*, max_components>;

class Component {
private:

public:
	Entity* entity;
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity {
private:
	Manager & manager;
	bool active = true;
	std::vector<std::unique_ptr<Component> > components;

	ComponentArray component_array;
	ComponentBitSet component_bit_set;
	GroupBitSet group_bit_set;

public:
	Entity(Manager& manager) : manager(manager) {

	}
	void update() {
		for (auto& c : components) c->update();
	}

	void draw() {
		for (auto& c : components) c->draw();
	}

	bool is_active() const {
		return active;
	}

	void destroy() {
		active = false;
	}

	bool has_group(Group group) {
		return group_bit_set[group];
	}

	void add_group(Group group);
	void del_group(Group group) {
		group_bit_set[group] = false;
	}

	template <typename T> bool has_component() const {
		return component_bit_set[get_component_type_ID<T>()];
	}

	template <typename T, typename... TArgs> 
	T& add_component(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		component_array[get_component_type_ID<T>()] = c;
		component_bit_set[get_component_type_ID<T>()] = true;

		c->init();

		return *c;
	}

	template<typename T> T& get_component() const {
		auto ptr(component_array[get_component_type_ID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity> > entities;
	std::array<std::vector<Entity*>, max_groups> grouped_entities;
public:
	void update() {
		for (auto& e : entities) e->update();
	}
	void draw() {
		for (auto& e : entities) e->draw();
	}

	void refresh() {
		for (auto i(0u); i < max_groups; i++) {
			auto& v(grouped_entities[i]);

			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* entity) 
			{
				return !entity->is_active() || !entity->has_group(i); 
			}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity> &mEntity)
		{
			return !mEntity->is_active();
		}),
			std::end(entities));
	}

	void add_to_group(Entity* entity, Group group) {
		grouped_entities[group].emplace_back(entity);
	}

	std::vector<Entity*>& get_group(Group group) {
		return grouped_entities[group];
	}

	Entity& add_entity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};