/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iostream>
#include <stack>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> &first,
                                const Point<Dim> &second, int curDim) const
{
  /**
     * @todo Implement this function!
     */
  if (first[curDim] == second[curDim])
  {
    return first < second;
  }
  return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> &target,
                                const Point<Dim> &currentBest,
                                const Point<Dim> &potential) const
{
  /**
     * @todo Implement this function!
     */
  double dTarget = 0;
  double dCurrent = 0;
  for (int i = 0; i < Dim; i++)
  {
    dTarget += std::pow(target[i] - potential[i], 2);
    dCurrent += std::pow(currentBest[i] - target[i], 2);
  }
  if (dTarget < dCurrent)
  {
    return true;
  }
  else if (dTarget > dCurrent)
  {
    return false;
  }
  else
  {
    return potential < currentBest;
  }

  return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>> &newPoints)
{
  /**
     * @todo Implement this function!
     */
  vector<Point<Dim>> points = newPoints;
  // random seed for random pivot selection in recursive calls to subtree
  srand(time(NULL));
  root = createSubtree(points, 0, points.size() - 1, 0);
  coordinates = points;
  size = std::log2(newPoints.size()) + 1;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim> &other)
{
  /**
   * @todo Implement this function!
   */
  this = new KDTree(other.coordinates);
}

// inclusive from indixes[a, b]
template <int Dim>
typename KDTree<Dim>::KDTreeNode *KDTree<Dim>::createSubtree(vector<Point<Dim>> &points, int a, int b, int curDim)
{
  if (b - a < 0)
  {
    return NULL;
  }
  if (b == a)
  {
    return new KDTreeNode(points[a]);
  }
  else
  {
    curDim %= Dim;
    int median = quickSelectN(points, a, b, curDim, (b - a) / 2);
    KDTreeNode *toReturn = new KDTreeNode(points[median]);
    toReturn->left = createSubtree(points, a, median - 1, curDim + 1);
    toReturn->right = createSubtree(points, median + 1, b, curDim + 1);

    return toReturn;
  }
}

template <int Dim>
const KDTree<Dim> &KDTree<Dim>::operator=(const KDTree<Dim> &rhs)
{
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree()
{
  /**
   * @todo Implement this function!
   */
  deleteNode(root);
}

template <int Dim>
void KDTree<Dim>::deleteNode(KDTreeNode *subRoot)
{
  if (subRoot == NULL)
  {
    return;
  }
  deleteNode(subRoot->left);
  deleteNode(subRoot->right);
  delete subRoot;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> &query) const
{
  /**
     * @todo Implement this function!
     */
  return findNearestNeighbor(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode *subroot, const Point<Dim> &query, int dimension) const
{
  if (subroot->left == NULL && subroot->right == NULL)
  {
    return subroot->point;
  }

  Point<Dim> currentBest = subroot->point;
  Point<Dim> potential = currentBest;

  bool left = smallerDimVal(query, currentBest, dimension);

  if (left && subroot->left != NULL)
  {
    potential = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
  }
  else if (!left && subroot->right != NULL)
  {
    potential = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
  }

  if (shouldReplace(query, currentBest, potential))
  {
    currentBest = potential;
  }

  double bestDist = distanceSquared(query, currentBest);
  double distDim = std::pow(query[dimension] - subroot->point[dimension], 2);
  if (distDim <= bestDist)
  {
    if (!left && subroot->left != NULL)
    {
      potential = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
      if (shouldReplace(query, currentBest, potential))
      {
        currentBest = potential;
      }
    }
    else if (left && subroot->right != NULL)
    {
      potential = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
      if (shouldReplace(query, currentBest, potential))
      {
        currentBest = potential;
      }
    }
  }
  return currentBest;
}

template <int Dim>
int KDTree<Dim>::quickSelectN(vector<Point<Dim>> &points, int a, int b, int curDim, int n)
{
  if (b - a == 0)
  {
    return a;
  }
  int pivot = partition(points, a, b, curDim);
  if (pivot - a == n)
  {
    return pivot;
  }

  else if (pivot - a > n)
  {
    return quickSelectN(points, a, pivot - 1, curDim, n);
  }
  else
  {
    return quickSelectN(points, pivot + 1, b, curDim, n - (pivot - a + 1));
  }
}

template <int Dim>
double KDTree<Dim>::distanceSquared(const Point<Dim> &first, const Point<Dim> &second) const
{
  double sum = 0;
  for (unsigned i = 0; i < Dim; ++i)
  {
    sum += std::pow(first[i] - second[i], 2);
  }
  return sum;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>> &points, int a, int b, int curDim)
{
  int randIndex = rand() % (b - a) + a;
  // put this index at the end to partition the vector slice
  Point<Dim> tmp = points[randIndex];
  points[randIndex] = points[b];
  points[b] = tmp;

  int pivot = a;
  for (int j = a; j < b; j++)
  {
    if (smallerDimVal(points[j], points[b], curDim))
    {
      tmp = points[j];
      points[j] = points[pivot];
      points[pivot] = tmp;
      pivot++;
    }
  }
  tmp = points[pivot];
  points[pivot] = points[b];
  points[b] = tmp;

  return pivot;
}