import addon from 'bindings';
const uhid: any = addon( 'node-uhid' );
import { EventEmitter } from 'events';


export enum UHIDBusType {
  PCI = uhid.UHIDBusType.PCI,
  ISAPNP = uhid.UHIDBusType.ISAPNP,
  USB = uhid.UHIDBusType.USB,
  HIL = uhid.UHIDBusType.HIL,
  BLUETOOTH = uhid.UHIDBusType.BLUETOOTH,
  VIRTUAL = uhid.UHIDBusType.VIRTUAL,
  ISA = uhid.UHIDBusType.ISA,
  I8042 = uhid.UHIDBusType.I8042,
  XTKBD = uhid.UHIDBusType.XTKBD,
  RS232 = uhid.UHIDBusType.RS232,
  GAMEPORT = uhid.UHIDBusType.GAMEPORT,
  PARPORT = uhid.UHIDBusType.PARPORT,
  AMIGA = uhid.UHIDBusType.AMIGA,
  ADB = uhid.UHIDBusType.ADB,
  I2C = uhid.UHIDBusType.I2C,
  HOST = uhid.UHIDBusType.HOST,
  GSC = uhid.UHIDBusType.GSC,
  ATARI = uhid.UHIDBusType.ATARI,
  SPI = uhid.UHIDBusType.SPI,
  RMI = uhid.UHIDBusType.RMI,
  CEC = uhid.UHIDBusType.CEC,
  INTEL_ISHTP = uhid.UHIDBusType.INTEL_ISHTP
}

export enum UHIDDevFlags {
  FEATURE = uhid.UHIDDevFlags.NUMBERED_FEATURE_REPORTS,
  OUTPUT = uhid.UHIDDevFlags.NUMBERED_OUTPUT_REPORTS,
  INPUT = uhid.UHIDDevFlags.NUMBERED_INPUT_REPORTS,
}

export enum UHIDReportType {
  FEATURE = uhid.UHIDReportType.FEATURE_REPORT,
  OUTPUT = uhid.UHIDReportType.OUTPUT_REPORT,
  INPUT = uhid.UHIDReportType.INPUT_REPORT,
}

export type UHIDStartEvent = {
  devFlags: UHIDDevFlags
};

export type UHIDOutputEvent = {
  data: Buffer,
  rtype: UHIDReportType
};

export type UHIDGetReportEvent = {
  id: number,
  rtype: UHIDReportType
};

export type UHIDSetReportEvent = {
  data: Buffer,
  id: number,
  rnum: number,
  rtype: UHIDReportType
};

export class UHIDDevice extends uhid.UHIDDevice {
  private eventEmitter: any;
  private eE = new EventEmitter();

  constructor () {
    super();
    this.eventEmitter = this.eE.emit.bind( this.eE );
  }

  on ( event: "start", listener: ( e: UHIDStartEvent ) => void ): void;
  on ( event: "stop", listener: () => void ): void;
  on ( event: "open", listener: () => void ): void;
  on ( event: "close", listener: () => void ): void;
  on ( event: "output", listener: ( e: UHIDOutputEvent ) => void ): void;
  on ( event: "getReport", listener: ( e: UHIDGetReportEvent ) => void ): void;
  on ( event: "setReport", listener: ( e: UHIDSetReportEvent ) => void ): void;

  on ( event: any, listener: any ): void {
    this.eE.on( event, listener );
  }

  once ( event: "start", listener: ( e: UHIDStartEvent ) => void ): void;
  once ( event: "stop", listener: () => void ): void;
  once ( event: "open", listener: () => void ): void;
  once ( event: "close", listener: () => void ): void;
  once ( event: "output", listener: ( e: UHIDOutputEvent ) => void ): void;
  once ( event: "getReport", listener: ( e: UHIDGetReportEvent ) => void ): void;
  once ( event: "setReport", listener: ( e: UHIDSetReportEvent ) => void ): void;

  once ( event: any, listener: any ): void {
    this.eE.once( event, listener );
  }

  off ( event: "start", listener: ( e: UHIDStartEvent ) => void ): void;
  off ( event: "stop", listener: () => void ): void;
  off ( event: "open", listener: () => void ): void;
  off ( event: "close", listener: () => void ): void;
  off ( event: "output", listener: ( e: UHIDOutputEvent ) => void ): void;
  off ( event: "getReport", listener: ( e: UHIDGetReportEvent ) => void ): void;
  off ( event: "setReport", listener: ( e: UHIDSetReportEvent ) => void ): void;

  off ( event: any, listener: any ): void {
    this.eE.off( event, listener );
  }

  create ( options: {
    name: string,
    data: Buffer,
    bus: UHIDBusType,
    vendor: number,
    product: number,
    version: number,
    country: number
  } ): void {
    super.create( options );
  }

  destroy (): void {
    super.destroy();
  }

  input ( data: Buffer ): void {
    super.input( data );
  }

  getReportReply ( options: { id: number, err: number, data: Buffer } ): void {
    super.getReportReply( options );
  }

  setReportReply ( options: { id: number, err: number } ): void {
    super.setReportReply( options );
  }

  poll (): void {
    super.poll();
  }

  open (): void {
    super.open();
  }

  close (): void {
    super.close();
  }

}