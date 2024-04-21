#pragma once
#include <iostream>


namespace my_list {

    template<typename ItemType>
    struct ListNode
    {

        using value_type = ItemType;

        value_type data_;
        ListNode<value_type> *next_;

        ListNode() = default;

        ListNode(value_type data) : data_(data)
        {}

        ListNode(value_type&& data)
        {
            data_ = std::move(data);
        }

    };

    template<typename ItemType>
    class LinkedList
    {

        using value_type = ItemType;

    public:

        LinkedList() : size_(0), head_(nullptr), tail_(nullptr)
        {}

        LinkedList(const value_type& item)
        {
            head_ = new ListNode<value_type>(item);

        }

        LinkedList(const LinkedList& right)
        {
            if (this == std::addressof(right))
                return;

            head_ = nullptr;
            size_ = 0;
            ListNode<value_type>* tmp = right.head_;

            while (tmp) {
                this->push_back(tmp->data_);
                tmp = tmp->next_;
            }
        }

        LinkedList& operator=(const LinkedList& right)
        {
            if (this == std::addressof(right))
                return *this;

            head_ = nullptr;
            size_ = 0;
            ListNode<value_type>* tmp = right.head_;

            while (tmp) {
                this->push_back(tmp->data_);
                tmp = tmp->next_;
            }
            return *this;
        }


        ~LinkedList()
        {
            clear();
        }

        size_t size()
        {
            return size_;
        }

        value_type front() {
            return head_->data_;
        }

        value_type back() {
            return tail_->data_;
        }


        value_type operator[](size_t index)
        {
            if (index < 0 || index >= size_)
                throw std::out_of_range("Index is out of range");

            return getNode(index)->data_;
        }

        void push_back(const value_type& item)
        {
            auto *tmp = new ListNode<value_type>();
            tmp->data_ = item;
            tmp->next_ = nullptr;

            if (!head_)
            {
                head_ = tmp;
                tail_ = head_;
            }
            else
            {
               tail_->next_ = tmp;
               tail_ = tail_->next_;
            }

            ++size_;
        }


        void insert(size_t index, value_type item)
        {
            if (size_ <= index)
                return push_back(item);

            auto *tmp = new ListNode<value_type>();
            tmp->data_ = item;

            if (index == 0)
            {
                tmp->next_ = head_;
                head_ = tmp;
            }

            auto prev_el = getNode(index - 1);

            tmp->next_ = prev_el->next_;
            prev_el->next_ = tmp;

            ++size_;
        }

        value_type pop_back()
        {
            if (size_ == 0)
                return value_type();


            if (size_ == 1) {
                value_type return_value = head_->data_;
                delete(head_);
                head_ = nullptr;
                tail_ = nullptr;
                size_ = 0;
                return return_value;
            }

            auto tmp = getNode(size_ - 2);
            value_type return_value = tmp->next_->data_;
            delete(tmp->next_);
            tmp->next_ = nullptr;
            tail_ = tmp;
            --size_;
            return return_value;
        }

        value_type remove(size_t index)
        {
            if (size_ == 0 || index < 0 || index >= size_)
                return value_type();

            if (index == 0)
            {
                value_type return_value = head_->data_;
                auto tmp = head_;
                head_ = head_->next_;
                delete tmp;
                --size_;
                return return_value;
            }

            if (index == size_ - 1)
                return pop_back();

            auto tmp = getNode(index - 1);
            auto node_to_delete = tmp->next_;
            value_type return_value = node_to_delete->next_->data_;
            tmp->next_ = node_to_delete->next_;
            delete node_to_delete;
            --size_;
            return return_value;
        }

        void clear() {
            ListNode<value_type>* tmp;
            while (head_)
            {
                tmp = head_;
                head_ = head_->next_;
                delete tmp;
            }
            tail_ = nullptr;
            size_ = 0;
        }

    private:
        size_t size_;
        ListNode<value_type> *head_;
        ListNode<value_type> *tail_;

        ListNode<value_type>* getNode(size_t index)
        {
            if (index >= size_)
                throw std::out_of_range("Index is out of range");

            if (index == 0)
                return head_;

            if (index == size_ - 1) {
                return tail_;
            }

            size_t counter = 0;
            auto tmp = head_;
            while (counter != index)
            {
                tmp = tmp->next_;
                ++counter;
            }
            return tmp;
        }
    };
}