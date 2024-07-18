//same tree
bool isSameTree(TreeNode* p, TreeNode* q) {
	if (p == NULL && q == NULL) return true;
	else if (!p || !q) return false;
	else {
		if (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right)) {
			return true;
		}
	}
	return false;
}
//symmetric tree
bool dfs(TreeNode* root1, TreeNode* root2) {
	if (!root1 && !root2) return true;
	if (!root1 || !root2) return false;
	if (root1->val != root2->val) return false;
	return dfs(root1->left, root2->right) && dfs(root1->right, root2->left);
}
bool isSymmetric(TreeNode* root) {
	if (root == NULL || (!root->left && !root->right))
		return true;
	return dfs(root->left, root->right);
}
//level order
vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> res;
	if (!root) return res;
	queue < TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		vector<int> v;
		int s = q.size();
		for (int i = 0; i < s; i++) {
			TreeNode* cur = q.front();
			q.pop();
			v.push_back(cur->val);
			if (cur->left != NULL) q.push(cur->left);
			if (cur->right != NULL) q.push(cur->right);
		}
		res.push_back(v);
	}
	return res;
}
//minimun depth
int minDepth(TreeNode* root) {
	if(!root) return 0;

	if(!root->left && !root->right) return 1;
	int left = INT_MAX, right = INT_MAX;
	if(root->left)
		left = minDepth(root->left);
	if(root->right)
		right = minDepth(root->right);

	return min(left, right) + 1;
}
//sum of deepest leaves
int maxDepth(TreeNode* root) {
	if (root == NULL) return 0;
	return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
int solve(TreeNode* &root, int depth) {
	if (root == NULL) return 0;
	--depth;
	if (depth == 0) return root->val;
	int l = 0, r = 0;
	l = solve(root->left, depth);
	r = solve(root->right, depth);
	return l + r;
}
int deepestLeavesSum(TreeNode* root) {
	if (root == NULL) return 0;
	int maxD = maxDepth(root);
	int ans = 0;
	ans = solve(root, maxD);
	return ans;
}
//two BST to array
void inorder(TreeNode* root, vector<int>& list) {
	if (root == NULL) return;
	inorder(root->left, list);
	list.push_back(root->val);
	inorder(root->right, list);
}
vector<int> merge2Arr(vector<int>& list1, vector<int>& list2) {
	int i = 0, j = 0;
	vector<int> list;
	int n = list1.size(), m = list2.size();
	while (i < n || j < m) {
		if (j >= m || (i < n && list1[i] <= list2[j])) {
			list.push_back(list1[i++]);
		} else {
			list.push_back(list2[j++]);
		}
	}
	return list;
}
vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
	vector<int> list1, list2;
	inorder(root1, list1);
	inorder(root2, list2);
	return merge2Arr(list1, list2);
}
//balanceBST
void createArray(TreeNode* root, vector<int>& arr) {
	if (root == NULL) return;
	createArray(root->left, arr);
	arr.push_back(root->val);
	createArray(root->right, arr);
}
TreeNode* buildTree(vector<int>& arr, int start, int end) {
	if (start > end) return NULL;
	int mid = (start + end) / 2;
	TreeNode* root = new TreeNode(arr[mid]);
	root->left = buildTree(arr, start, mid - 1);
	root->right = buildTree(arr, mid + 1, end);

	return root;
}

TreeNode* balanceBST(TreeNode* root) {
	vector<int> arr;
	createArray(root, arr);
	int n = arr.size();
	return buildTree(arr, 0, n - 1);
}

//path sum ii
void pathS(TreeNode* root, vector<vector<int>> &res, vector<int> &path, int targetSum) {
	if(!root) return;

	targetSum -= root->val;
	path.push_back(root->val);

	if(!root->left && !root->right) {
		if(targetSum == 0)
			res.push_back(path);
		path.pop_back();
		return;
	}

	pathS(root->left, res, path, targetSum);
	pathS(root->right, res, path, targetSum);
	path.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
	vector<vector<int>> res;
	vector<int> tmp;
	pathS(root, res, tmp, targetSum);
	return res;
}
//invert tree
TreeNode* invertTree(TreeNode* root) {
	if (root == NULL || (!root->left && !root->right)) return root;
	else {
		TreeNode* tmp = root->left;
		root->left = invertTree(root->right);
		root->right = invertTree(tmp);
	}
	return root;
}
//kth smallest element
void solve(TreeNode* root, int& cnt, int& k, int& ans) {
	if (root == NULL) return;

	solve(root->left, cnt, k, ans);
	cnt++;
	if (cnt == k) {
		ans = root->val;
		return;
	}
	solve(root->right, cnt, k, ans);
}
int kthSmallest(TreeNode* root, int k) {
	int ans;
	int cnt = 0;
	solve(root, cnt, k, ans);
	return ans;
}
//binary tree path
void solve(TreeNode* root, vector<string>& res, string val) {
	if (root == NULL) return;
	if (val != "") {
		val += "->";
		cout << val << " ";
	}
	val += to_string(root->val);

	if (root->left == NULL && root->right == NULL) {
		res.push_back(val);
	} else {
		solve(root->left, res, val);
		solve(root->right, res, val);
	}
}

vector<string> binaryTreePaths(TreeNode* root) {
	vector<string> res;
	string val = "";
	solve(root, res, val);
	return res;
}
//Input: root = [1,2,3,null,5]
//Output: ["1->2->5","1->3"]

//delete node
TreeNode* findMinNode(TreeNode* root) {
	if (root == NULL || root->left == NULL) return root;
	return findMinNode(root->left);
}

TreeNode* deleteNode(TreeNode* root, int key) {
	if (root == NULL) return NULL;
	else if (root->val < key) root->right = deleteNode(root->right, key);
	else if (root->val > key) root->left = deleteNode(root->left, key);
	else {
		// woo... complete finding the required node
		//case 1: no child
		if (root->right == NULL && root->left == NULL) {
			delete root;
			root = NULL;
		}
		//case 2: 1 child
		else if (root->right == NULL) {
			TreeNode* tmp = root;
			root = root->left;
			delete tmp;
		} else if (root->left == NULL) {
			TreeNode* tmp = root;
			root = root->right;
			delete tmp;
		}
		//case 3: 2 children
		else {
			TreeNode* tmp = findMinNode(root->right);
			root->val = tmp->val;
			root->right = deleteNode(root->right, tmp->val);
		}
	}
	return root;
}
//find mode
vector<int> findMode(TreeNode* root) {
	vector<int> ans;
	int currnum = 0;
	int currcnt = 0;
	int currmax = 0;
	TreeNode *node = root;
	while (node != nullptr) {
		while (node->left != nullptr) {
			// find frd
			TreeNode *frd = node->left;
			while (frd->right != nullptr) frd = frd->right;
			frd->right = node;
			TreeNode *prev = node;
			node = node->left;
			prev->left = nullptr;
		}

		int num = node->val;
		if (num == currnum) {
			currcnt++;
		} else {
			currcnt = 1;
			currnum = num;
		}

		if (currcnt > currmax) {
			currmax = currcnt;
			ans.clear();
		}

		if (currcnt == currmax) {
			ans.push_back(currnum);
		}

		node = node->right;
	}
	return ans;
}
//minimum abs difference
TreeNode* prevVal {nullptr};
void dfs(TreeNode* root, int& minDiff) {
	if (root == NULL) return;
	dfs(root->left, minDiff);
	if (prevVal) {
		minDiff = std::min(minDiff, std::abs(prevVal->val - root->val));
	}
	prevVal = root;
	dfs(root->right, minDiff);
}
int getMinimumDifference(TreeNode* root) {
	int minDiff = 1000000;
	// TreeNode* prevVal = NULL;
	// dfs(root, prevVal, minDiff);
	dfs(root, minDiff);
	return minDiff;
}
//subtree sametree
bool isSameTree(TreeNode* root, TreeNode* subRoot) {
	if (root == NULL && subRoot == NULL) return true;
	else if (!root|| !subRoot) return false;
	if (root->val == subRoot->val) {
		if (isSameTree(root->left, subRoot->left) && isSameTree(root->right, subRoot->right))
			return true;
	}
	return false;
}
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
	if (root == NULL) return subRoot == NULL;
	if (isSameTree(root, subRoot)) return true;
	return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}
//merge
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
	if (root1 == NULL) return root2;
	if (root2 == NULL) return root1;
	root1->val += root2->val;
	if (root2->left)
		root1->left = mergeTrees(root1->left, root2->left);
	if (root2->right)
		root1->right = mergeTrees(root1->right, root2->right);
	return root1;
}
//average of levels
vector<double> averageOfLevels(TreeNode* root) {
	vector<double> res;
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		int s = q.size();
		double cnt = 0, avg = 0;
		for (int i = 0; i < s; i++) {
			TreeNode* cur = q.front();
			q.pop();
			avg += (double) cur->val;
			cnt++;
			if (cur->left) q.push(cur->left);
			if (cur->right) q.push(cur->right);
		}
		res.push_back(avg / cnt);
	}
	return res;
}
//trim BST
TreeNode* trimBST(TreeNode* root, int low, int high) {
	if (!root) return root;
	if (root->val >= low && root->val <= high) {
		root->left = trimBST(root->left, low, high);
		root->right = trimBST(root->right, low, high);
		return root;
	}
	if (root->val < low) {
		return trimBST(root->right, low, high);
	}
	return trimBST(root->left, low, high);
}
//insert to BST
TreeNode* insertIntoBST(TreeNode* root, int val) {
	if(!root) return new TreeNode {val, NULL, NULL};
	if(val > root->val) root->right = insertIntoBST(root->right, val);
	if(val < root->val) root->left = insertIntoBST(root->left, val);
	return root;
}
//minumum distance btw nodes
void inorder(TreeNode* root, int& mini, int& prev) {
	if (root == NULL) return;
	inorder(root->left, mini, prev);
	if (prev != -1)
		mini = min(mini, abs(root->val - prev));
	prev = root->val;
	inorder(root->right, mini, prev);
}
int minDiffInBST(TreeNode* root) {
	int mini = INT_MAX;
	int prev = -1;
	inorder(root, mini, prev);
	return mini;
}
//increasing
TreeNode* increasingBST(TreeNode* root, TreeNode* tail = NULL) {
	if (!root) return tail;
	TreeNode* res = increasingBST(root->left, root);
	root->left = NULL;
	root->right = increasingBST(root->right, tail);
	return res;

}
//range sum
void dfs(TreeNode* root, int low, int high, int& res) {
	if (root == NULL) return;
	if (root->val >= low && root->val <= high) res += root->val;
	dfs(root->left, low, high, res);
	dfs(root->right, low, high, res);
}

int rangeSumBST(TreeNode* root, int low, int high) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int res = 0;
	dfs(root, low, high, res);
	return res;
}
//valid BST
bool IsBstUtil(TreeNode* root, long long minVal, long long maxVal) {
	if (root == NULL)
		return true;

	if (root->val > minVal && root->val < maxVal
	        && IsBstUtil(root->left, minVal, root->val)
	        && IsBstUtil(root->right,root->val, maxVal)) {
		return true;
	}

	return false;
}
bool isValidBST(TreeNode* root) {
	return IsBstUtil(root, LONG_MIN, LONG_MAX);
}
//recovery BST
void inorderAdd(TreeNode* root, vector<int>& a) {
	if (root == NULL) return;
	inorderAdd(root->left, a);
	a.push_back(root->val);
	cout << root->val << " ";
	inorderAdd(root->right, a);
}
void inorder(TreeNode* root, vector<int>& a, int& i) {
	if (root == NULL) return;
	inorder(root->left, a, i);
	root->val = a[i++];
	inorder(root->right, a, i);
}
void recoverTree(TreeNode* root) {
	vector<int> a;
	inorderAdd(root, a);
	sort(a.begin(), a.end());
	int i = 0;
	inorder(root, a, i);
}
