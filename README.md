# DiffServ
> This application will allow for different types of Queueing, and includes example implementations of Deficit Round Robin (DRR) and Strict Priority Queueing (SPQ)

## Migrating Code into NS-3

Pull the entire repo into a new folder named project2.  Now go to your NS-3 installation folder. From here you will go to the /src folder and place the newly created repo folder into it. For example, it would look something like this ```/ns-3.29/src/project2```, where /ns-3.29 is our current installation of NS-3.

The ```nlohmann``` folder and ```config.json``` file must be copied into the NS-3 root folder, where ```src``` is.

The four ```point-to-point...``` files in ```/project2/model``` must be copied into ```src/point-to-point/model```.

To use the actual application, copy over the ```project2.cc``` file over to ns-3.29/scratch. This is where you can run the application without rebuilding all the examples every time.

If you would like to add new files to the application, models will go in the model folder, examples in the example folder, etc... To ensure these get built correctly, make sure to edit the corresponding `wscript` files. New examples require the wscript in /examples to be updated. These files are where you can tell waf what modules, classes, etc. your application is going to be using. When waf builds ns3 again, your module will know what other headers it needs to include when running. 

## Building the Code

Now that all the files are copied to the right locations, go to the root of your ns3 installation (like ns-3.29 from earlier) and do


```
./waf configure -d optimized --enable-examples --enable-tests
```

This lets waf configure any example and tests you would want to use. Enabling examples is crucial to running your applications from the folder.

Next, run the following command to build the new applications. This will allow NS-3 to properly configure and link the applications with the existing ones originally included.

```
./waf build
```

To run a module, simply do a command like the following: 

```
./waf --run <module name>
```

Additionally, you some applications allow you to input additional parameters into the command line to change the way it runs. This application requires you to input the path to the config file that has the number of queues, priority of each queue, etc. For this program this command would be the following:

```
./waf --run "spq-example --config=config.json"
```

This command will run the SPQ example.

