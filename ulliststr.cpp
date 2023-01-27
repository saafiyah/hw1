#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last - 1]; 
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc > size_ || loc < 0) 
  {
    return NULL;
  }
  else
  {
    Item* curr = head_;
    while (loc >= (curr->last - curr->first))
    {
      loc = loc - (curr->last - curr->first);
      curr = curr->next; 
    }
    return &curr->val[curr->first + loc];
  }
}

void ULListStr::push_back(const std::string& val)
{
  if(empty() || tail_->last == ARRSIZE)
  {
    Item* newp = new Item(); 
    newp->last++;
    newp->val[0] = val;
    if(empty())
    {
      head_ = newp;
    }
    else if(tail_->last == ARRSIZE)
    {
      newp->prev = tail_;
      tail_->next = newp;
    }
    tail_ = newp; 
  }
  else
  {
    tail_->val[tail_->last] = val; 
    tail_->last++;
  }
  ++size_;
}

void ULListStr::push_front(const std::string& val)
{
  if(empty())
  {
    Item* newp = new Item(); 
    ++newp->last;
    newp->val[0] = val;
    head_ = newp;
    tail_ = newp; 
  }
  else if(head_->first == 0)
  {
    Item* newp = new Item(); 
    head_->prev = newp; 
    newp->next = head_;
    newp->val[ARRSIZE - 1] = val;
    newp->first = ARRSIZE - 1;
    newp->last = ARRSIZE;
    head_ = newp; 
  }
  else
  {
    head_->val[head_->first - 1] = val; 
    --head_->first;
  }
  ++size_;
}

void ULListStr::pop_back()
{
  if(empty())
  {
    return; 
  }
  else
  {
    tail_->last--; 
    --size_; 
  }
}

void ULListStr::pop_front()
{
	if(empty())
  {
    return; 
  }
	if(size_ == 1 && head_ == tail_)
	{
		tail_ = nullptr;
		delete head_;
		head_ = nullptr;
	}
	else if(head_->first != head_->last-1)
	{
		head_->first++; 
	}
	else
	{
		Item* temp = head_;
		head_ = head_->next; 
		head_->prev = nullptr; 
		delete temp; 
	}
	--size_; 
}

// {
//   if(empty())
//   {
//     return; 
//   }
//   else
//   {
//     head_->first++; 
//     --size_; 
//   }
// }

//dont change 

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
