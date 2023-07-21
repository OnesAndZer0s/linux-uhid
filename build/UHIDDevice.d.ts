/// <reference types="node" />
declare const uhid: any;
export declare enum UHIDBusType {
    PCI,
    ISAPNP,
    USB,
    HIL,
    BLUETOOTH,
    VIRTUAL,
    ISA,
    I8042,
    XTKBD,
    RS232,
    GAMEPORT,
    PARPORT,
    AMIGA,
    ADB,
    I2C,
    HOST,
    GSC,
    ATARI,
    SPI,
    RMI,
    CEC,
    INTEL_ISHTP
}
export declare enum UHIDDevFlags {
    FEATURE,
    OUTPUT,
    INPUT
}
export declare enum UHIDReportType {
    FEATURE,
    OUTPUT,
    INPUT
}
export declare type UHIDStartEvent = {
    devFlags: UHIDDevFlags;
};
export declare type UHIDOutputEvent = {
    data: Buffer;
    rtype: UHIDReportType;
};
export declare type UHIDGetReportEvent = {
    id: number;
    rtype: UHIDReportType;
};
export declare type UHIDSetReportEvent = {
    data: Buffer;
    id: number;
    rnum: number;
    rtype: UHIDReportType;
};
export declare class UHIDDevice extends uhid.UHIDDevice {
    private eventEmitter;
    private eE;
    constructor();
    on(event: "start", listener: (e: UHIDStartEvent) => void): void;
    on(event: "stop", listener: () => void): void;
    on(event: "open", listener: () => void): void;
    on(event: "close", listener: () => void): void;
    on(event: "output", listener: (e: UHIDOutputEvent) => void): void;
    on(event: "getReport", listener: (e: UHIDGetReportEvent) => void): void;
    on(event: "setReport", listener: (e: UHIDSetReportEvent) => void): void;
    once(event: "start", listener: (e: UHIDStartEvent) => void): void;
    once(event: "stop", listener: () => void): void;
    once(event: "open", listener: () => void): void;
    once(event: "close", listener: () => void): void;
    once(event: "output", listener: (e: UHIDOutputEvent) => void): void;
    once(event: "getReport", listener: (e: UHIDGetReportEvent) => void): void;
    once(event: "setReport", listener: (e: UHIDSetReportEvent) => void): void;
    off(event: "start", listener: (e: UHIDStartEvent) => void): void;
    off(event: "stop", listener: () => void): void;
    off(event: "open", listener: () => void): void;
    off(event: "close", listener: () => void): void;
    off(event: "output", listener: (e: UHIDOutputEvent) => void): void;
    off(event: "getReport", listener: (e: UHIDGetReportEvent) => void): void;
    off(event: "setReport", listener: (e: UHIDSetReportEvent) => void): void;
    create(options: {
        name: string;
        data: Buffer;
        bus: UHIDBusType;
        vendor: number;
        product: number;
        version: number;
        country: number;
    }): void;
    destroy(): void;
    input(data: Buffer): void;
    getReportReply(options: {
        id: number;
        err: number;
        data: Buffer;
    }): void;
    setReportReply(options: {
        id: number;
        err: number;
    }): void;
    poll(): void;
    open(): void;
    close(): void;
}
export {};
