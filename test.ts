import { UHIDBusType, UHIDDevice } from "./UHIDDevice";

const rdesc = [
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x02,	/* USAGE (Mouse) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x09, 0x01,		/* USAGE (Pointer) */
	0xa1, 0x00,		/* COLLECTION (Physical) */
	0x85, 0x01,			/* REPORT_ID (1) */
	0x05, 0x09,			/* USAGE_PAGE (Button) */
	0x19, 0x01,			/* USAGE_MINIMUM (Button 1) */
	0x29, 0x03,			/* USAGE_MAXIMUM (Button 3) */
	0x15, 0x00,			/* LOGICAL_MINIMUM (0) */
	0x25, 0x01,			/* LOGICAL_MAXIMUM (1) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x75, 0x01,			/* REPORT_SIZE (1) */
	0x81, 0x02,			/* INPUT (Data,Var,Abs) */
	0x95, 0x01,			/* REPORT_COUNT (1) */
	0x75, 0x05,			/* REPORT_SIZE (5) */
	0x81, 0x01,			/* INPUT (Cnst,Var,Abs) */
	0x05, 0x01,			/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x30,			/* USAGE (X) */
	0x09, 0x31,			/* USAGE (Y) */
	0x09, 0x38,			/* USAGE (WHEEL) */
	0x15, 0x81,			/* LOGICAL_MINIMUM (-127) */
	0x25, 0x7f,			/* LOGICAL_MAXIMUM (127) */
	0x75, 0x08,			/* REPORT_SIZE (8) */
	0x95, 0x03,			/* REPORT_COUNT (3) */
	0x81, 0x06,			/* INPUT (Data,Var,Rel) */
	0xc0,			/* END_COLLECTION */
	0xc0,		/* END_COLLECTION */
	0x05, 0x01,	/* USAGE_PAGE (Generic Desktop) */
	0x09, 0x06,	/* USAGE (Keyboard) */
	0xa1, 0x01,	/* COLLECTION (Application) */
	0x85, 0x02,		/* REPORT_ID (2) */
	0x05, 0x08,		/* USAGE_PAGE (Led) */
	0x19, 0x01,		/* USAGE_MINIMUM (1) */
	0x29, 0x03,		/* USAGE_MAXIMUM (3) */
	0x15, 0x00,		/* LOGICAL_MINIMUM (0) */
	0x25, 0x01,		/* LOGICAL_MAXIMUM (1) */
	0x95, 0x03,		/* REPORT_COUNT (3) */
	0x75, 0x01,		/* REPORT_SIZE (1) */
	0x91, 0x02,		/* Output (Data,Var,Abs) */
	0x95, 0x01,		/* REPORT_COUNT (1) */
	0x75, 0x05,		/* REPORT_SIZE (5) */
	0x91, 0x01,		/* Output (Cnst,Var,Abs) */
	0xc0,		/* END_COLLECTION */
];

var device = new UHIDDevice();

device.on( "start", ( e ) => {
	console.log( "start ", e );
} );

device.on( "stop", () => {
	console.log( "stop" );
} );

device.on( "open", () => {
	console.log( "open" );
} );

device.on( "close", () => {
	console.log( "close" );
} );

device.on( "output", ( e ) => {
	console.log( "output ", e );
} );

device.on( "getReport", ( e ) => {
	console.log( "getReport ", e );
} );

device.on( "setReport", ( e ) => {
	console.log( "setReport ", e );
} );


console.log( device );

device.open();

device.create( {
	name: "node-uhid-device",
	data: Buffer.from( rdesc ),
	bus: UHIDBusType.USB,
	vendor: 0x15d9,
	product: 0x0a37,
	version: 0x0001,
	country: 0x06
} );

var flip = false;
setInterval( () => {
	var buf = Buffer.alloc( 5 );
	flip = !flip;
	buf[ 0 ] = 0x1; // idk
	buf[ 1 ] = ( flip ) ? 0x1 : 0x0; // mouse
	// buf[ 2 ] = Math.random() * 100 - 50; // horiz move
	// buf[ 3 ] = Math.random() * 100 - 50; // vert move
	buf[ 4 ] = 0x0; // wheel
	device.input( buf );

}, 75 );

