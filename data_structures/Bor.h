#ifndef TWITTERTRENDSOOPLAB_BOR_H
#define TWITTERTRENDSOOPLAB_BOR_H

#include <unordered_map>
#include <optional>
#include <vector>
#include <stdexcept>
#include <functional>

namespace entity {
    template <typename T, typename V>
    class Bor {
    public:
        struct Node {
            using key_type = T;
            using mapped_type = Node;
            using value_type = V;

            std::unordered_map<key_type, mapped_type> children;
            std::optional<value_type> end_value;

            std::optional<std::reference_wrapper<const Node>> get_child(key_type key) const {
                auto it = children.find(key);
                return it != children.end()
                       ? std::optional(std::cref(it->second))
                       : std::nullopt;
            }
        };

        using key_type = T;
        using value_type = typename Node::value_type;
        using node_type = Node;
        using const_node_reference = const node_type&;
        using node_optional = std::optional<std::reference_wrapper<const node_type>>;

    private:
        node_type root;

        template <typename InputIt>
        const node_type* traverse(InputIt begin, InputIt end) const {
            const node_type* current = &root;
            for (auto it = begin; it != end; ++it) {
                auto child = current->children.find(*it);
                if (child == current->children.end()) return nullptr;
                current = &child->second;
            }
            return current;
        }

    public:
        template <typename InputIt>
        void insert(InputIt begin, InputIt end, const value_type& value) {
            node_type* current = &root;
            for (auto it = begin; it != end; ++it) {
                current = &current->children[*it];
            }
            current->end_value = value;
        }

        template <typename InputIt>
        bool contains(InputIt begin, InputIt end) const {
            const node_type* node = traverse(begin, end);
            return node && node->end_value.has_value();
        }

        template <typename InputIt>
        std::optional<value_type> get_value(InputIt begin, InputIt end) const {
            const node_type* node = traverse(begin, end);
            return node ? node->end_value : std::nullopt;
        }

        template <typename InputIt>
        bool update_value(InputIt begin, InputIt end, const value_type& new_value) {
            node_type* node = const_cast<node_type*>(traverse(begin, end));
            if (!node || !node->end_value) return false;
            node->end_value = new_value;
            return true;
        }

        template <typename InputIt>
        bool erase(InputIt begin, InputIt end) {
            std::vector<node_type*> path;
            node_type* current = &root;
            path.push_back(current);

            for (auto it = begin; it != end; ++it) {
                auto child = current->children.find(*it);
                if (child == current->children.end()) return false;
                current = &child->second;
                path.push_back(current);
            }

            if (!current->end_value) return false;
            current->end_value.reset();

            for (int i = path.size()-1; i > 0; --i) {
                if (path[i]->children.empty() && !path[i]->end_value) {
                    T key = *std::next(begin, i-1);
                    path[i-1]->children.erase(key);
                } else {
                    break;
                }
            }
            return true;
        }

        node_optional get_next(const_node_reference node, key_type key) const {
            return node.get_child(key);
        }

        const_node_reference root_node() const { return root; }

        bool is_end_node(const_node_reference node) const {
            return node.end_value.has_value();
        }
    };
} // namespace entity

#endif //TWITTERTRENDSOOPLAB_BOR_H