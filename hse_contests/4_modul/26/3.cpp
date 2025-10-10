#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>

using namespace std;

class PersistentQueue {
    struct Node {
        enum Type { INIT, PUSH, POP };
        Type type;
        int parent_id;
        int val;
        int result_index;
        
        Node(Type t, int p, int v = 0, int ri = -1) 
            : type(t), parent_id(p), val(v), result_index(ri) {}
    };

    std::vector<Node> operatrs;
    std::vector<std::vector<int> > oper_tree;
    std::vector<int> deleted_results;
    std::vector<std::pair<Node::Type, int> > histrory_oper;

public:
    PersistentQueue() { operatrs.emplace_back(Node::INIT, -1); oper_tree.emplace_back();  }

    void parse_operations(int total) {
        for (int i = 1; i <= total; ++i) {
            std::string op_type; std::cin >> op_type;

            if (op_type == "1") {
                int per_op, val; cin >> per_op >> val;
                add_push(per_op, val);
            } else {
                int per_op; std::cin >> per_op;
                add_pop(per_op);
            }
        }
    }

    void pr_oper() {
        std::deque<int> current_queue;
        depth(0, current_queue);
    }

    void printt() const {
        for (int res : deleted_results) {
            std::cout << res << '\n';
        }
    }

private:
    void add_push(int parent_id, int val) {
        operatrs.emplace_back(Node::PUSH, parent_id, val);
        oper_tree.emplace_back();
        oper_tree[parent_id].push_back(operatrs.size() - 1);
    }

    void add_pop(int parent_id) {
        operatrs.emplace_back(Node::POP, parent_id, 0, deleted_results.size());
        oper_tree.emplace_back();
        oper_tree[parent_id].push_back(operatrs.size() - 1);
        deleted_results.push_back(0); 
    }

    void depth(int op_id, std::deque<int>& queue) {
        const Node& current_op = operatrs[op_id];

        switch (current_op.type) {
            case Node::PUSH:
                queue.push_back(current_op.val);
                histrory_oper.emplace_back(Node::PUSH, 0);
                break;
                
            case Node::POP:
                if (!queue.empty()) {
                    int front_value = queue.front();
                    queue.pop_front();
                    deleted_results[current_op.result_index] = front_value;
                    histrory_oper.emplace_back(Node::POP, front_value);
                }
                break;
                
            case Node::INIT:
                break;
        }

        for (int child_id : oper_tree[op_id]) {
            depth(child_id, queue);
        }

        if (op_id != 0 && !histrory_oper.empty()) {
            auto [last_op_type, last_value] = histrory_oper.back();
            histrory_oper.pop_back();

            if (last_op_type == Node::PUSH) {
                queue.pop_back();
            } else if (last_op_type == Node::POP) {
                queue.push_front(last_value);
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int total; std::cin >> total;

    PersistentQueue q;
    q.parse_operations(total);
    q.pr_oper();
    q.printt();

    return 0;
}