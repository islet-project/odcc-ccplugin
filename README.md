# Apply Android CC to your service with CCPlugin

## What is CCPlugIn?

CCPlugIn allows developers to run their Java services in a Realm environment on Android. It bridges the Normal World and the Realm World, enabling secure and isolated execution of custom services.

## Prerequisites
Please follow this [Android CC Environment Setup](https://github.com/islet-project/odcc-islet-script-qemu-rme/blob/main/README.md) to set up the environment for using Host Android as a VM host and running KVM-based virtual machines.

## How to apply CCPlugIn into your repository

### `@GenerateCCService` on your AIDL interface

To run an AIDL interface inside a Realm via CCPlugIn, you must annotate the **AIDL interface** with:

`@GenerateCCService(FQCN="...")`

`FQCN` is the **fully-qualified class name** of the Realm-side service implementation that CCPlugIn should launch and bind to this interface.

Example:

```java
// This FQCN string should be matched with your own service's FQCN.
@GenerateCCService(FQCN="com.example.realm.MyCcService")
interface IExampleInterface
{
    void doSomething();
    int addInt(int a, int b);
    int getRandomNumber();
    void getRandomNumberFromCallback(IResponse response);
    ...
}
```

### Copy `ccplugin_template` into your repository
```bash
cd <AOSP ROOT>/external/CCPlugIn
./copy_ccplugin_template.sh <TARGET REPO ROOT>
cd <TARGET REPO ROOT>
cat ccplugin_template/append_to_your_android_bp.txt >> <TARGET ANDROID.BP PATH>/Android.bp
```

After that, you need to fill in the blanks in your `Android.bp` file. Here's an example
```
// The main service file of your app which runs in the Realm world. It should be a java file.
filegroup {
    name: "my_app_service_for_realm",
    srcs: [""], // NOTE: Please fill in this part
}

/*
 * The actual implementation of this interface runs on "my_app_service_for_realm" in the Realm world.
 * The CCProxyService uses this interface to relays requests from the Normal World to the Realm world.
 */
filegroup {
    name: "my_app_aidl_for_realm",
    srcs: [""], // NOTE: Please fill in this part
}
```

Please define your own app name and replace "my_app" to it in both your Android.bp
and ccplugin_template/Android.bp.
```
android_app {
    name: "my_app", // NOTE: Please define your own app name here
    srcs: [
        ":generate_cc_service",
    ],
    ...
}
```

Refer to these sample apps to learn how to apply CCPlugIn to your service:
- [odcc-example-aosp](https://github.com/islet-project/odcc-example-aosp/tree/on-device-cc)
- [odcc-tf-lite-bert-qa](https://github.com/islet-project/odcc-tf-lite-bert-qa)

In case your service uses the remote provisioning mechanism, you can configure a whitelist of allowed
provisioning servers. Once a whitelist is configured, the confidential service will be able to connect only
to a predefined list of provisioning servers. The list also defines the hard limit of transmitted bytes imposed on the outgoing direction i.e.
from the Realm VM to provisioning servers.

To configure the whitelist mechanism, you need to create and place a file named `whitelist.json` inside the `assets` folder of the service application. The file should contain an array of objects in JSON format.

Each JSON object should contain following fields:

- `address` - an IP address or hostname of a provisioning server
- `port` - the port on which the provisioning server is listening
- `protocol` - the protocol that is used by the provisioning server (`Tcp` or `Udp`, currently the provisioning mechanism uses only `Tcp` protocol)
- `tx_bytes_limit` - the hard limit of send bytes, usually it should be set to some small arbitrary value that would safely send a TLS handshake and an
                     HTTP request; note that usually the Realm VM receives much more data (e.g. ML models) than it sends outside the device.

Here is an example content of `whitelist.json` file used for provisioning of TensorFlow Lite BERT QA model:

```json
[
	{ "address": "192.168.97.1", "port": 1337, "protocol": "Tcp", "tx_bytes_limit": 4096 }
]
```

## Building

```
UNBUNDLED_BUILD_SDKS_FROM_SOURCE=true TARGET_BUILD_APPS=<YOUR ANDROID_APP NAME> m apps_only dist
```

## Installing

You can install the app like this:
```
adb install -t out/dist/<YOUR ANDROID_APP NAME>.apk
```
