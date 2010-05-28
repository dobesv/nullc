// std.list
import std.typeinfo;

class list_node
{
	list_node ref prev, next;
	auto ref elem;
}
auto ref list_node.value()
{
	return elem;
}
class list
{
	typeid	elemType;
	int		anyType;

	list_node ref first;
	list_node ref last;
}

list list()
{
	list ret;
	ret.anyType = 1;
	ret.elemType = auto ref;
	ret.first = ret.last = nullptr;
	return ret;
}

list list(typeid type)
{
	list ret;
	ret.anyType = 0;
	ret.elemType = type;
	ret.first = ret.last = nullptr;
	return ret;
}

void list:push_back(auto ref elem)
{
	if(!anyType && typeid(elem) != (isPointer(elemType) ? elemType.subType() : elemType))
		assert(0, "list::push_back argument type (" + typeid(elem).name + ") differs from list element type (" + elemType.name + ")");
	if(!first)
	{
		first = last = new list_node;
		first.prev = first.next = nullptr;
		first.elem = isPointer(elemType) ? elem : duplicate(elem);
	}else{
		last.next = new list_node;
		last.next.prev = last;
		last.next.next = nullptr;
		last = last.next;
		last.elem = isPointer(elemType) ? elem : duplicate(elem);
	}
}
void list:push_front(auto ref elem)
{
	if(!anyType && typeid(elem) != elemType)
		assert(0, "list::push_front argument type (" + typeid(elem).name + ") differs from list element type (" + elemType.name + ")");
	if(!first)
	{
		first = last = new list_node;
		first.prev = first.next = nullptr;
		first.elem = isPointer(elemType) ? elem : duplicate(elem);
	}else{
		first.prev = new list_node;
		first.prev.next = first;
		first.prev.prev = nullptr;
		first = first.prev;
		first.elem = isPointer(elemType) ? elem : duplicate(elem);
	}
}
void list:insert(list_node ref it, auto ref elem)
{
	if(!anyType && typeid(elem) != elemType)
		assert(0, "list::insert argument type (" + typeid(elem).name + ") differs from list element type (" + elemType.name + ")");
	auto next = it.next;
	it.next = new list_node;
	it.next.elem = isPointer(elemType) ? elem : duplicate(elem);
	it.next.prev = it;
	it.next.next = next;
	if(next)
		next.prev = it.next;
}
void list:erase(list_node ref it)
{
	auto prev = it.prev, next = it.next;
	if(prev)
		prev.next = next;
	if(next)
		next.prev = prev;
	if(it == first)
		first = first.next;
	if(it == last)
		last = last.prev;
}
void list:clear()
{
	first = last = nullptr;
}
auto ref list:back()
{
	assert(first != nullptr, "list::back called on empty list");
	return last.elem;
}
auto ref list:front()
{
	assert(first != nullptr, "list::front called on empty list");
	return first.elem;
}
auto list:begin()
{
	return first;
}
auto list:end()
{
	return last;
}

// iteration
class list_iterator
{
	list_node ref curr;
}
auto list_iterator(list_node ref start)
{
	list_iterator ret;
	ret.curr = start;
	return ret;
}
auto list:start()
{
	return list_iterator(this.first);
}
auto list_iterator:next()
{
	auto ref ret = curr.elem;
	curr = curr.next;
	return ret;
}
auto list_iterator:hasnext()
{
	return curr ? 1 : 0;
}
