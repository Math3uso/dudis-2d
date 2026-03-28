export abstract class DDCommand<TOptions = any> {
    abstract name: string;
    abstract desc: string;
    abstract configure(): {
        arguments?: { name: string; required?: boolean }[];
        options?: {
            flags: string;
            description: string;
            required?: boolean;
            defaultValue?: any;
        }[];
    };

    abstract execute(
        args: Record<string, string>,
        options: TOptions
    ): Promise<void> | void;
}