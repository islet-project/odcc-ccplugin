/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=java -Weverything -Wno-missing-permission-annotation -Werror -Wno-mixed-oneway --min_sdk_version current --ninja -o external/CCPlugIn/gen -N . -N vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig vendor/samsung/odcc-example-aosp/OdccExampleServiceOrig/com/examplecc/service/IExampleInterface.aidl
 */
package com.examplecc.service;
/**
 * This is the service exposed by the test payload, called by the test app.
 * {@hide}
 */
public interface IExampleInterface extends android.os.IInterface
{
  /** Default implementation for IExampleInterface. */
  public static class Default implements com.examplecc.service.IExampleInterface
  {
    @Override public void doSomething() throws android.os.RemoteException
    {
    }
    @Override public int addInt(int a, int b) throws android.os.RemoteException
    {
      return 0;
    }
    @Override public int getRandomNumber() throws android.os.RemoteException
    {
      return 0;
    }
    @Override public void getRandomNumberFromCallback(com.examplecc.service.IResponse response) throws android.os.RemoteException
    {
    }
    @Override
    public android.os.IBinder asBinder() {
      return null;
    }
  }
  /** Local-side IPC implementation stub class. */
  public static abstract class Stub extends android.os.Binder implements com.examplecc.service.IExampleInterface
  {
    /** Construct the stub at attach it to the interface. */
    @SuppressWarnings("this-escape")
    public Stub()
    {
      this.attachInterface(this, DESCRIPTOR);
    }
    /**
     * Cast an IBinder object into an com.examplecc.service.IExampleInterface interface,
     * generating a proxy if needed.
     */
    public static com.examplecc.service.IExampleInterface asInterface(android.os.IBinder obj)
    {
      if ((obj==null)) {
        return null;
      }
      android.os.IInterface iin = obj.queryLocalInterface(DESCRIPTOR);
      if (((iin!=null)&&(iin instanceof com.examplecc.service.IExampleInterface))) {
        return ((com.examplecc.service.IExampleInterface)iin);
      }
      return new com.examplecc.service.IExampleInterface.Stub.Proxy(obj);
    }
    @Override public android.os.IBinder asBinder()
    {
      return this;
    }
    @Override public boolean onTransact(int code, android.os.Parcel data, android.os.Parcel reply, int flags) throws android.os.RemoteException
    {
      java.lang.String descriptor = DESCRIPTOR;
      if (code >= android.os.IBinder.FIRST_CALL_TRANSACTION && code <= android.os.IBinder.LAST_CALL_TRANSACTION) {
        data.enforceInterface(descriptor);
      }
      if (code == INTERFACE_TRANSACTION) {
        reply.writeString(descriptor);
        return true;
      }
      switch (code)
      {
        case TRANSACTION_doSomething:
        {
          this.doSomething();
          reply.writeNoException();
          break;
        }
        case TRANSACTION_addInt:
        {
          int _arg0;
          _arg0 = data.readInt();
          int _arg1;
          _arg1 = data.readInt();
          data.enforceNoDataAvail();
          int _result = this.addInt(_arg0, _arg1);
          reply.writeNoException();
          reply.writeInt(_result);
          break;
        }
        case TRANSACTION_getRandomNumber:
        {
          int _result = this.getRandomNumber();
          reply.writeNoException();
          reply.writeInt(_result);
          break;
        }
        case TRANSACTION_getRandomNumberFromCallback:
        {
          com.examplecc.service.IResponse _arg0;
          _arg0 = com.examplecc.service.IResponse.Stub.asInterface(data.readStrongBinder());
          data.enforceNoDataAvail();
          this.getRandomNumberFromCallback(_arg0);
          reply.writeNoException();
          break;
        }
        default:
        {
          return super.onTransact(code, data, reply, flags);
        }
      }
      return true;
    }
    private static class Proxy implements com.examplecc.service.IExampleInterface
    {
      private android.os.IBinder mRemote;
      Proxy(android.os.IBinder remote)
      {
        mRemote = remote;
      }
      @Override public android.os.IBinder asBinder()
      {
        return mRemote;
      }
      public java.lang.String getInterfaceDescriptor()
      {
        return DESCRIPTOR;
      }
      @Override public void doSomething() throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain(asBinder());
        android.os.Parcel _reply = android.os.Parcel.obtain();
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          boolean _status = mRemote.transact(Stub.TRANSACTION_doSomething, _data, _reply, 0);
          _reply.readException();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
      }
      @Override public int addInt(int a, int b) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain(asBinder());
        android.os.Parcel _reply = android.os.Parcel.obtain();
        int _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeInt(a);
          _data.writeInt(b);
          boolean _status = mRemote.transact(Stub.TRANSACTION_addInt, _data, _reply, 0);
          _reply.readException();
          _result = _reply.readInt();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      @Override public int getRandomNumber() throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain(asBinder());
        android.os.Parcel _reply = android.os.Parcel.obtain();
        int _result;
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          boolean _status = mRemote.transact(Stub.TRANSACTION_getRandomNumber, _data, _reply, 0);
          _reply.readException();
          _result = _reply.readInt();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
        return _result;
      }
      @Override public void getRandomNumberFromCallback(com.examplecc.service.IResponse response) throws android.os.RemoteException
      {
        android.os.Parcel _data = android.os.Parcel.obtain(asBinder());
        android.os.Parcel _reply = android.os.Parcel.obtain();
        try {
          _data.writeInterfaceToken(DESCRIPTOR);
          _data.writeStrongInterface(response);
          boolean _status = mRemote.transact(Stub.TRANSACTION_getRandomNumberFromCallback, _data, _reply, 0);
          _reply.readException();
        }
        finally {
          _reply.recycle();
          _data.recycle();
        }
      }
    }
    static final int TRANSACTION_doSomething = (android.os.IBinder.FIRST_CALL_TRANSACTION + 0);
    static final int TRANSACTION_addInt = (android.os.IBinder.FIRST_CALL_TRANSACTION + 1);
    static final int TRANSACTION_getRandomNumber = (android.os.IBinder.FIRST_CALL_TRANSACTION + 2);
    static final int TRANSACTION_getRandomNumberFromCallback = (android.os.IBinder.FIRST_CALL_TRANSACTION + 3);
  }
  /** @hide */
  public static final java.lang.String DESCRIPTOR = "com.examplecc.service.IExampleInterface";
  public void doSomething() throws android.os.RemoteException;
  public int addInt(int a, int b) throws android.os.RemoteException;
  public int getRandomNumber() throws android.os.RemoteException;
  public void getRandomNumberFromCallback(com.examplecc.service.IResponse response) throws android.os.RemoteException;
}
