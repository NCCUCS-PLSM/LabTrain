package edu.nccu.plsm.train.c;

import edu.nccu.plsm.train.b.MyObject2;

import java.util.Iterator;
import java.util.Spliterator;

/**
 * @param <T> the type of elements in this collection
 */
public class MyObject3<T> extends MyObject2<T> {

    @Override
    public Iterator<T> iterator() {
        return super.iterator();
    }

    @Override
    public Spliterator<T> spliterator() {
        return super.spliterator();
    }

    @Override
    public boolean equals(Object obj) {
        return super.equals(obj);
    }

    @Override
    public int hashCode() {
        return super.hashCode();
    }


    @Override
    public String toString() {
        return super.toString();
    }

}
