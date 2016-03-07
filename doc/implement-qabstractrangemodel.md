# Implementing the  QAbstractRangeModel

To implement the QAbstractRangeModel, we must first understand how the QRangeView and QAbstractRangeModel
communicate with each other. Since items are loaded according to their position, the QRangeView doesn't 
need to know the number of items within the model, nor their indexes. This means that the model can store
items in linked-lists, trees or other container types as long as it can manage to find items between specific
ranges. The boundaries of the model are configured by the ```contentLength``` property of the model.

Since item indexes are not used, identification of items between the model and the view is done
through an items position, length and relative index. The relative index is used in case 2 items with the
same position and length are present, and refers to the order in which the item was received from the model.
The following table provides an example: 

 Position | Length | Relative Index
 -------- | ------ | --------------
 10       | 5      | 0
 15       | 5      | 0
 15       | 5      | 1
 20       | 5      | 0
 
The second and third items are differentiated by their relative index, which helps the view identify a specific
item for the model.


## Read-only model

For a **read-only model** the following methods are required:

 * the ```contentWidth``` **property** needs to be set so the view knows the width of the model:

```cpp
CustomModel::CustomModel(QObject* parent = 0)
: QAbstractRangeModel(parent)
{
	setContentWidth(1000);
}
```
 
 * the ```roleNames()``` function is implemented to map item data. It doesn't include the item position and length
   properties, which are already defined in the QAbstractRangeModel. This functionality provides the same means of 
   accessing data as the QAbstractItemModel:

```cpp
    // in our header file, we define the Role enum

    class CustomModel : public QAbstractRangeModel{
    // ...
    public:
        // custom roles are next in line after the position and length role

        enum Role{
            modelData = QAbstractRangeModel::LengthRole + 1
        };
    // ...
    QHash<int, QByteArray> roleNames() const;
    // ...
    }
```

```cpp
    // Then we map our enum to property names

    QHash<int, QByteArray> CustomModel::roleNames() const{
        QHash<int, QByteArray> roles;
        roles[QGanttModel::ModelData] = "modelData";
        return roles;
    }
```
  
 * ```dataBetween(startPosition, endPosition)``` - returns an iterable set of items to display between startPosition and endPosition
   Items need to be ordered in ascending order according to their position and length. The items are returned in the form
   of a ```QAbstractRangeModelIterator```. The iterator is called by the view and iterates through the given items, and provides the
   data for the view from the set ```roleNames()```. The iterator will be deleted by the view once it reaches the end of the model.
 
```cpp
QAbstractRangeModelIterator* CustomModel::dataBetween(qint64 startPosition, qint64 endPosition){
    // ItemIterator is used as an example, and will be used only internally by the CustomModelIterator to iterate items. This can be
    // an iterator for any container type defined by the user.

    ItemIterator start = itemIteratorFromPosition(startPosition);
    ItemIterator end   = itemIteratorFromPosition(endPosition);
    return new CustomModelIterator(start, end);
}
```

Where a ```CustomModelIterator``` implements ```isEnd()```, ```nextItem()``` and ```data(int role)``` from
```QAbstractRangeModelIterator```:

```cpp
class CustomModelIterator : public QAbstractRangeModelIterator{
    CustomModelIterator(ItemIterator current, ItemIterator end) : m_current(current), m_end(end){}

    bool isEnd() const{ return m_start == m_end; }
    void nextItem(){ ++m_current; }

    QVariant data(int role = 0){
        if ( role == CustomModel::PositionRole ) return m_current->position;
        else if ( role == CustomModel::LengthRole) return m_current->length;
        else if ( role == CustomModel::ModelData) return m_current->data;
        else return QVariant();
    }

private:
    ItemIterator m_start;
    ItemIterator m_end;
}
```


## Writable model

To make the model **writable**, an extra set of methods requires implementation:
 
 * the ```setItemPosition()``` function is called when the view requests an item to change its position. The item is 
 searched for within the model, assigned a new position, then the view is notified through the 
 itemCoordinatesChanged() signal:
 
```

```

 * setItemLength() behaves the same as setItemPosition()

```

```
  
 * setItemData() sets custom data to the model from the given role names

```

```
 
 * ```insertItem(position, length)``` - inserts an item in the model at the specified position and length. 
   The view is notified by calling ```beginDataChange(startPosition, endPosition)``` and 
   ```endDataChange()``` methods:
 
```
void CustomModel::insertItem(qint64 position, qint64 length){
	beginDataChange(position, position + length);
	insertItem(new CustomModelItem(position, length));
	endDataChange();
}
```
 
 * removeItem(position, length, relativeIndex) - remove the item at the specified coordinates. The view is notified
 through the same 2 methods as the insertion:

```
void CustomModel::removeItem(qint64 position, qint64 length, qint64 relativeIndex){
	CustomModelItem* item = findItem(position, length, relativeIndex);
	if (item){
		beginDataChange(position, position + length);
		removeItem(item);
		endDataChange();
	}
}
```
  
  * The ```beginDataChange(startPosition, endPosition)``` and ```endDataChange()``` are used whenever the 
    model wants to notify the view over a set of items that have changed between those positions. Changes 
	to the whole model can be notified by signalling a change between 0 and the contentWidth of the model:
  
```
void CustomModel::resetModel(){
	beginDataChange(0, contentWidth());
	clearData();
	endDataChange();
}
```

## Example

The default ```QGanttModel``` provided in the library is an implementation of a QAbstractRangeModel.
