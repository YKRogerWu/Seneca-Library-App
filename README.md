# Project: Seneca Library Application
This application was made in an attempt to manage books in a library so that they are easily retrievable manageable. 
> This project was under the instruction provided from the course Object Orinted Programming (course code: OOP244) at Seneca College, written by [prof. Soleimanloo](https://github.com/fardad) & [prof. Mardini](https://github.com/wailmardini).

### Description
This app recognizes two major kind of literature, *publication* and *book*. The former, such as magazine and newspaper, is only allowed to read in the library and cannot be borrowed. The latter, on the other hand, can be checked out at the counter but need to be returned no later than the due date. All information about the library literature are recorded in a data sheet named ***LibRecs.txt*** by default. The major feature of the Library App are:

##### Add New Publication
Assuming when new books or publications are arrived, their book identities are registered and put on the shelves so that the furtur actions can be done. When a new book/publication is registered, the information below will be required to enter:

Book type 
    categorize the literature into book(B) or publication(P)

Shelf no
    indicate the shelf location where the book/publication is stowed
```text
format: 1 alphabet + 3 digits
e.g. P001, T123
```

Title 
    the title of the literature (up to 255 characters in length), the exceeding charaters will be truncated

Date
the date that the literature is registered
```text
format: yyyy-mm-dd
```
Author
    the author name of the literature (up to 15 character), the exceeding charaters will be truncated

#### Remove Publication
If a book longer exists, this functionality removes it from the data sheet.

#### Checkout Publication from Library
When books are brought to check-out counter from the shelves, staff uses this functionality to mark the book with "borrowed" tag and the due day of the borrowed book starts to count. Meanwhile, the book will no longer be available for another customer until it is returned.
#### Return Publication to Library
It removes the borrowed tag from a book in the data sheet and the returned book will open to borrow. If the book is returned later than the due date, a penalty fee will be attracted which accumulated on a daily basis.

### Data Sheet Format
When looking into the data sheet, generally the format are like:
```text
Book   Book     Shelf                       Member  Checkout
type    ID      No          Book Title      ID*     Date         Author
-----|--------|-----|---------------------|-------|------------|---------|
B       1009	U818	The Da Vinci Code	0   	2021-11-19	Dan Brown
P       1037	P002	The Toronto SUN	    0	    2021-11-18

*note: a book is available when its *Member ID* shows "0", otherwise it displays the member number of the book borrower.
```
